#include "cmds.h"
#include "redisstore.h"

std::unordered_map<std::string, redis_func_type> cmd_map = {
    {"ping", redis_ping},
    {"echo", redis_echo},
    {"set",  redis_set},
    {"get",  redis_get},
    {"config",  redis_config},};


redis_func_type get_redis_func(const std::string& cmd_name) {

    auto it = cmd_map.find(cmd_name);
    if (it != nullptr) {
        return it->second;
    }
    // Should not reach here
    throw RedisServerError(cmd_name + " not found!");
}


cmd_ret_type redis_ping(const std::vector<std::string>& req) {

    if (req.size() == 0 || req[0] != "ping") {
        throw RedisServerError("Bad input");
    }

    if (req.size() > 2) {
        return std::make_unique<redis::Error>
        ("ERR wrong number of arguments for 'ping' command");
    }
    if (req.size() == 1) {
        // no arguments provided, return simple string
        return std::make_unique<redis::SimpleString>("PONG");
    }

    // return a bulk string of the argument if any
    return std::make_unique<redis::BulkString>(req[1]);
}

cmd_ret_type redis_echo(const std::vector<std::string>& req) {

    if (req.size() == 0 || req[0] != "echo") {
        throw RedisServerError("Bad input");
    }

    if (req.size() != 2) {
        return std::make_unique<redis::Error>
        ("ERR wrong number of arguments for 'echo' command");
    }
    return std::make_unique<redis::SimpleString>(req[1]);
}


cmd_ret_type redis_set(const std::vector<std::string>& req) {

    if (req.size() == 0 || req[0] != "set") {
        throw RedisServerError("Bad input");
    }

    std::time_t expiry_epoch = LONG_MAX;
    int i = 3;
    if (req.size() < 3) {
        goto syntax_error;
    }

    while(i < req.size()) {
        if (req[i] == "EX") {
            i++;
            if (i >= req.size()) {
                goto syntax_error;
            }
            std::time_t expiry_from_now;
            try {
                expiry_from_now = std::stol(req[i]);
            } catch (const std::exception& e) {
                goto out_of_range;
            }
            auto now = std::chrono::system_clock::now();
            auto expiry = now + std::chrono::seconds(expiry_from_now);
            expiry_epoch =  std::chrono::system_clock::to_time_t(expiry);

        } else if (req[i] == "PX") {
            i++;
            if (i >= req.size()) {
                goto syntax_error;
            }
            std::time_t expiry_from_now;
            try {
                expiry_from_now = std::stol(req[i])/1000;
            } catch (const std::exception& e) {
                goto out_of_range;
            }
            auto now = std::chrono::system_clock::now();
            auto expiry = now + std::chrono::seconds(expiry_from_now);
            expiry_epoch =  std::chrono::system_clock::to_time_t(expiry);

        } else if (req[i] == "EXAT") {
            i++;
            if (i >= req.size()) {
                goto syntax_error;
            }
            try {
                expiry_epoch = std::stol(req[i]);
            } catch (const std::exception& e) {
                goto out_of_range;
            }
        } else if (req[i] == "PXAT") {
            i++;
            if (i >= req.size()) {
                goto syntax_error;
            }
            try {
                expiry_epoch = std::stol(req[i])/1000;
            } catch (const std::exception& e) {
                goto out_of_range;
            }
        } else {
            goto syntax_error;
        }
        ++i;
    }

    RedisStore::getInstance().set(req[1], req[2], expiry_epoch);
    return std::make_unique<redis::SimpleString>("OK");

    syntax_error:
    return std::make_unique<redis::Error>("ERR syntax error");

    out_of_range:
    return std::make_unique<redis::Error>("ERR value is not an integer or out of range");

}

cmd_ret_type redis_get(const std::vector<std::string>& req) {

    if (req.size() == 0 || req[0] != "get") {
        throw RedisServerError("Bad input");
    }

    if (req.size() != 2) {
        return std::make_unique<redis::Error>
        ("ERR wrong number of arguments for 'get' command");
    }
    std::string output;
    bool found = RedisStore::getInstance().get(req[1], output);

    if (!found) {
        return std::make_unique<redis::NullString>();
    }
    return std::make_unique<redis::SimpleString>(output);
}

cmd_ret_type redis_config_get(const std::vector<std::string>& req) {

    std::unique_ptr<redis::Array> arr = std::make_unique<redis::Array>();
    arr->add_element(std::make_unique<redis::BulkString>("900"));
    arr->add_element(std::make_unique<redis::BulkString>("1"));
    return arr; // move not required because of RVO
}

cmd_ret_type redis_config(const std::vector<std::string>& req) {

    if (req.size() == 0 || to_lower(req[0]) != "config") {
        throw RedisServerError("Bad input");
    }

    return redis_config_get(req);
}


