myRedis
-------

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
redis-benchmark -t set,get, -n 100000 -q
SET: 222222.23 requests per second
GET: 222717.16 requests per second
```

Building myRedis
----------------

Let's say the path you cloned this repo is `$REDIS_HOME`. Steps to build myRedis:
```
$export REDIS_HOME=/path/to/your/clone
$cd $REDIS_HOME
$mkdir ${REDIS_HOME}/bin
$cd bin
$cmake $REDIS_HOME
$make
```

This will create the executable named `redis` in `${REDIS_HOME}\bin` directory.

Running myRedis
----------------

To run myRedis, just do:
```
$cd $REDIS_HOME
$bin/redis
```

This will start a myRedis server at port 2000 (You can change that in `config.json` file).

You should see an output like below if you are running this for the first time:
```
$bin/redis
State restoral failed! Continuing with empty state...
Server listening on port: 2000
```

(More on state restoral below)

Note that you must run this executable from your `$REDIS_HOME` directory, as myRedis assumes that a 
`config.json` file is present in the directory the executable is being run in.

Talking to myRedis
------------------

You can talk to myRedis using official [redis-cli](https://redis.io/docs/latest/develop/connect/cli/)! In a different terminal you can try the following:
```
$redis-cli -p 2000
127.0.0.1:2000> ping
PONG
127.0.0.1:2000> echo "this is myRedis"
this is myRedis
127.0.0.1:2000> set name1 ram 
OK
127.0.0.1:2000> get name1
ram
127.0.0.1:2000> rpush statement myRedis looks interesting!
(integer) 3
127.0.0.1:2000> lrange statement 0 -1
1) "myRedis"
2) "looks"
3) "interesting!"
127.0.0.1:2000> save
OK
```

Key choices of myRedis
----------------------


Source code layout
------------------


Improvements
------------



