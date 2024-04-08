#include <chrono>
#include "redisstore.h"

RedisStore* RedisStore::_Instance = nullptr;
std::mutex RedisStore::_Instancemutex;
RedisStore::data_type RedisStore::data;

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

void RedisStore::set_with_expiry_epoch(const std::string& key, const std::string& value, const std::time_t expiry_epoch) {
    std::unique_lock<std::shared_mutex> lock(_datamutex);
    data[key] = {value, expiry_epoch};
}

void RedisStore::set_with_expiry_from_now(const std::string& key, const std::string& value, const std::time_t expiry_from_now_in_sec) {
    std::unique_lock<std::shared_mutex> lock(_datamutex);
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::seconds(expiry_from_now_in_sec);
    std::time_t expiry_epoch = std::chrono::system_clock::to_time_t(expiry);
    data[key] = {value, expiry_epoch};
}

bool RedisStore::get(const std::string& key, std::string& value) const {

    bool remove_key = false;
    {
        std::shared_lock<std::shared_mutex> lock(_datamutex);
        auto it = data.find(key);
        if (it != data.end()) {
            auto now = std::chrono::system_clock::now();
            std::time_t now_epoch = std::chrono::system_clock::to_time_t(now);

            if (it->second.expiry_epoch > now_epoch) {
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