#include <chrono>
#include "redisstore.h"

RedisStore* RedisStore::_Instance = nullptr;
std::mutex RedisStore::_Instancemutex;
RedisStore::data_type RedisStore::data;
RedisStore::list_type RedisStore::list_data;

RedisStore& RedisStore::getInstance() {

    if (_Instance == nullptr) {
        std::lock_guard<std::mutex> lock(_Instancemutex);
        if (_Instance == nullptr) {
            _Instance = new RedisStore();
        }
    }
    return *_Instance;
}

void RedisStore::delInstance() {
    
    if (_Instance != nullptr) {
        std::lock_guard<std::mutex> lock(_Instancemutex);
        if (_Instance != nullptr) {
            _Instance->clear();
            delete _Instance;
            _Instance = nullptr;
        }
    }
}

void RedisStore::clear() {
    std::unique_lock<std::shared_mutex> lock(_datamutex);
    data.clear();

}

void RedisStore::set(const std::string& key, const std::string& value, const std::time_t expiry_epoch) {
    std::unique_lock<std::shared_mutex> lock(_datamutex);
    data[key] = {value, expiry_epoch}; // never expires
}

static std::time_t now_epoch() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}

bool RedisStore::get(const std::string& key, std::string& value) const {

    bool remove_key = false;
    {
        std::shared_lock<std::shared_mutex> lock(_datamutex);
        auto it = data.find(key);
        if (it != data.end()) {

            if (it->second.expiry_epoch > now_epoch()) {
                value = it->second.val;
                return true;
            } else {
                // key expired, remove it
                remove_key = true;
                // can not upgrade to unique lock here as it
                // can lead to deadlock with another get call
            }
        }
    }
    if (remove_key) {
        // lazy removal
        std::unique_lock<std::shared_mutex> lock(_datamutex);
        data.erase(key);
    }
    return false;
}

bool RedisStore::exists(const std::string& key) const {

    static std::string temp;
    return get(key, temp);
}

int RedisStore::erase(const std::string& key) {
    std::unique_lock<std::shared_mutex> lock(_datamutex);
    return data.erase(key);
}

/**
 * reverse set to true means decr
*/
int RedisStore::incr(const std::string& key, bool reverse) {
    std::unique_lock<std::shared_mutex> lock(_datamutex);
    std::string str_val;
    auto it = data.find(key);
    if (it != data.end() && it->second.expiry_epoch > now_epoch()) {
        int64_t int_val;
        try{
            int_val = std::stoll(it->second.val);
        } catch (const std::exception& e) {
            throw e;
        }
        int delta = reverse ? -1 : 1;
        str_val = std::to_string(int_val+delta);
        it->second.val = str_val;
        return int_val+delta;
    } else {
        data[key] = {reverse ? "-1" : "1", LONG_MAX};
        return reverse ? -1 : 1;
    }

    // should not reach here
    return -1;
}

int RedisStore::lpush(const std::string& key, const std::vector<std::string>& vals, bool reverse) {

    std::unique_lock<std::shared_mutex> lock(_listmutex);

    auto it = list_data.find(key);
    if (it == list_data.end()) {
        // maybe this is not required
        list_data[key] = {};
    }

    for (auto val : vals) {
        if (reverse) {
            list_data[key].push_back(val);
        } else {
            list_data[key].push_front(val);
        }
    }

    return list_data[key].size();

}

std::vector<std::string> RedisStore::lrange(const std::string& key, int start, int end) {
    std::shared_lock<std::shared_mutex> lock(_listmutex);
    auto it = list_data.find(key);
    if (it == list_data.end()) {
        return {};
    }

    if (start < 0) {
        start = it->second.size() + start;
        if (start < 0) {
            // I think this should return empty list
            // unless we are wrapping around
            return {};
        }
    }
    if (end < 0) {
        end = it->second.size() + end;
        if (end < 0) {
            // I think this should return empty list
            // unless we are wrapping around
            return {};
        }
    }
    if (end >= it->second.size()) {
        end = it->second.size()-1;
    }
    if (start > end) {
        return {};
    }
    std::vector<std::string> res;
    for (int i=start; i<=end && i < it->second.size(); i++) {
        res.push_back(it->second[i]);
    }
    return res;
}