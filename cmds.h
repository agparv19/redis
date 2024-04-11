#pragma once
#include<unordered_map>
#include "common.h"
#include "type.h"

using cmd_ret_type = std::unique_ptr<redis::RObject>; 

#define REDIS_CMD(NAME) cmd_ret_type redis_##NAME(const std::vector<std::string>& req);

using redis_func_type = std::function<cmd_ret_type(const std::vector<std::string>&)>;

REDIS_CMD(ping)
REDIS_CMD(echo)
REDIS_CMD(set)
REDIS_CMD(get)
REDIS_CMD(exists)
REDIS_CMD(del)
REDIS_CMD(incr)
REDIS_CMD(decr)
REDIS_CMD(lpush)
REDIS_CMD(rpush)
REDIS_CMD(lrange)
REDIS_CMD(config)


redis_func_type get_redis_func(const std::string& cmd_name);
