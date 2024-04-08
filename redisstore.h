#include "common.h"
#include <shared_mutex>

struct ValueEntry {
    std::string val;
    std::time_t expiry_epoch; 
};

class RedisStore {

    typedef std::unordered_map<std::string, ValueEntry> data_type; 

    public:

    static RedisStore& getInstance();
    static void delInstance();

    void set(const std::string& key, const std::string& value, const std::time_t expiry_epoch = LONG_MAX);
    void set_with_expiry_epoch(const std::string& key, const std::string& value, const std::time_t expiry_epoch);
    void set_with_expiry_from_now(const std::string& key, const std::string& value, const std::time_t expiry_from_now_in_sec);
    bool get(const std::string& key, std::string& value) const;
    void clear();

    RedisStore(const RedisStore&) = delete;
    RedisStore& operator=(const RedisStore&) = delete;

    private:

    static data_type data;

    RedisStore() {}
    ~RedisStore() {}

    static RedisStore* _Instance;
    static std::mutex _Instancemutex;
    mutable std::shared_mutex _datamutex; 
        

};