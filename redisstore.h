#include "common.h"
#include <shared_mutex>
#include <deque>
#include <nlohmann/json.hpp>

#define STATEFILE "/home/agparv19/codemill/redis/state.json"

struct ValueEntry {
    std::string val;
    std::time_t expiry_epoch; 
};

class RedisStore {

    typedef std::unordered_map<std::string, ValueEntry> data_type; 
    typedef std::unordered_map<std::string, std::deque<std::string>> list_type;

    public:

    static RedisStore& getInstance();
    static void delInstance();

    void set(const std::string& key, const std::string& value, const std::time_t expiry_epoch = LONG_MAX);
    bool get(const std::string& key, std::string& value) const;
    bool exists(const std::string& key) const;
    int erase(const std::string& key);
    int incr(const std::string& key, bool reverse = false);
    int lpush(const std::string& key, const std::vector<std::string>& vals, bool reverse = false);
    std::vector<std::string> lrange(const std::string& key, int start, int end);
    bool dump();
    bool restore();
    void clear();

    RedisStore(const RedisStore&) = delete;
    RedisStore& operator=(const RedisStore&) = delete;

    private:

    static data_type data;
    static list_type list_data;

    RedisStore() {}
    ~RedisStore() {}

    static RedisStore* _Instance;
    static std::mutex _Instancemutex;
    mutable std::shared_mutex _datamutex; 
    mutable std::shared_mutex _listmutex; 
        

};