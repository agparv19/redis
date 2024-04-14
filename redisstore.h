#include "common.h"
#include <shared_mutex>
#include <deque>
#include <nlohmann/json.hpp>

#define STATEFILE "state.json"

/**
 * To expiry of values
*/
struct ValueEntry {
    std::string val;
    std::time_t expiry_epoch; 
};

/**
 * This is a singleton class.
 * RedisStore represents all the data stored in redis
*/
class RedisStore {

    typedef std::unordered_map<std::string, ValueEntry> data_type; 
    typedef std::unordered_map<std::string, std::deque<std::string>> list_type;

    public:

    /**
     * Returns the singleton instance of this class.
    */
    static RedisStore& getInstance();

    /**
     * Deletes the singleton instance of this class.
    */
    static void delInstance();

    /**
     * set a {key, {value, expiry}}
     * stores in data map.
    */
    void set(const std::string& key, const std::string& value, const std::time_t expiry_epoch = LONG_MAX);
    
    /**
     * get a value of key from data map, return false if
     * key does not exists or is expired.
     * If key is expired, it is also removed.
    */
    bool get(const std::string& key, std::string& value) const;

    /**
     * Checkd if there is an entry for a key in
     * RedisStore (check both data and list_data maps).
    */
    bool exists(const std::string& key) const;

    /**
     * Remove a key from RedisStore
    */
    int erase(const std::string& key);

    /**
     * Increment the value if it can be converted to integer
     * Decrements if reverse = true
    */
    int incr(const std::string& key, bool reverse = false);

    /**
     * Push the vals from left,
     * if reverse = true, then push from right
    */
    int lpush(const std::string& key, const std::vector<std::string>& vals, bool reverse = false);

    /**
     * get the value of key in a given range
     * return empty array if key isn't present in list_data
    */
    std::vector<std::string> lrange(const std::string& key, int start, int end);

    /**
     * Dump the in-memory state of redis to disk
    */
    bool dump();

    /**
     * load the in-memory state of redis from disk
    */
    bool restore();

    /**
     * clear out all the data from RedisStore
    */
    void clear();

    RedisStore(const RedisStore&) = delete;
    RedisStore& operator=(const RedisStore&) = delete;

    private:

    static data_type data;
    static list_type list_data;

    RedisStore() {}
    ~RedisStore() {}

    static RedisStore* _Instance;
    /**
     * mutex to synchronize access to _Instance
    */
    static std::mutex _Instancemutex;

    /**
     * mutexes to synchronize data
    */
    mutable std::shared_mutex _datamutex; 
    mutable std::shared_mutex _listmutex; 
};
