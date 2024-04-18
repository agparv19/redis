This is my implementation of popular in-memory key-value database [Redis](https://github.com/redis/redis) from scratch in C++. (referred to as myRedis in rest of this doc)

myRedis supports the same operations as the actual version of Redis at launch in 2009. The list of commands supported are:

- [SET](https://redis.io/docs/latest/commands/set/)
- [GET](https://redis.io/docs/latest/commands/get/)
- [EXISTS](https://redis.io/docs/latest/commands/exists/)
- [DEL](https://redis.io/docs/latest/commands/del/)
- [INCR](https://redis.io/docs/latest/commands/incr/)
- [DECR](https://redis.io/docs/latest/commands/decr/)
- [LPUSH](https://redis.io/docs/latest/commands/lpush/)
- [RPUSH](https://redis.io/docs/latest/commands/rpush/)
- [LRANGE](https://redis.io/docs/latest/commands/lrange/)
- [SAVE](https://redis.io/docs/latest/commands/save/)


Performance 
-----------

Here is a benchmark of how myRedis performs:

```
redis-benchmark -p 2000 -t set,get, -n 100000 -q
SET: 207468.88 requests per second
GET: 213675.22 requests per second
```

For comparison here is how current version of redis performs:
```
agparv19:~$redis-benchmark -t set,get, -n 100000 -q
SET: 222222.23 requests per second
GET: 222717.16 requests per second
```

Building myRedis
----------------

Let's say the path you cloned this repo is $REDIS_HOME


