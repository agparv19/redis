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

The objective of this project is just to build a functional key-value database application from scratch. myRedis is not written with an aim to overperform official redis in some metric, but rather to deeply understand how Redis and server applications in C++ works. 

Performance 
-----------

Here is a benchmark of how myRedis performs:

```
redis-benchmark -p 2000 -t set,get, -n 100000 -q
SET: 207468.88 requests per second
GET: 213675.22 requests per second
```

For comparison here is how current official version of redis performs:
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
There are few ways myRedis is different from official implementation. 

- myRedis uses one thread per client connection, as opposed to single threaded event loop architecture of official redis
    - main reason to choose this was ease of implementation
    - working with async io code in c++ seems to be quite messy
- myRedis being multi-threaded implements necessary locking to protect data race
- myRedis supports persistence to disk by dumping snapshot of myRedis data into a `state.json` file in `$REDIS_HOME`. This is unlike official redis which uses binary `rdb` file. If there exists a `state.json` file in `$REDIS_HOME` dir from its last run, myRedis will load this file at startup, otherwise will run with an empty state.
    - chose `json` just because it is human readable, and I wanted to see changes to data in action on running `save` redis cmd
    - at some point in future, I may consider moving this to a binary format like `protobuf` or `rdb` itself
- myRedis supports to two configs via `config.json` file in `$REDIS_HOME` dir:
    - `port`: the port at which you want your myRedis server to run
    - `snapshot_period`: the time period (in minutes) of periodic snapshot of myRedis' in-memory state


Source code layout
===

Following are the important files:

CMakeLists.txt
--------------
Contains information on how to build myRedis executable.

server.cpp
----------
This is the main file, which starts up the server and launches a new thread for every client connection. This also creates the snapshot thread which periodically wakes up after a fixed time interval to dump myRedis' state.

RESPParser.cpp (.h)
-------------------
Redis uses [RESP](https://redis.io/docs/latest/develop/reference/protocol-spec/) protocol to exchange messages between server and client. 

Each client request is an [array](https://redis.io/docs/latest/develop/reference/protocol-spec/#arrays) of [bulk strings](https://redis.io/docs/latest/develop/reference/protocol-spec/#bulk-strings). This file implements the deserialization logic of the client request including the logic to read from client `fd`.

Since RESP uses `\r\n` (CRLF) to separate two meaningful items, a RESP parser would have to process the serialized message item by item. Instead of reading item by item from socket, myRedis has a read cache of `8192` bytes which prevents parser from making large number of expensive `read` syscalls.

Each client thread have a RESPParser object which exposes `read_new_request()` method.

redisstore.cpp (.h)
-------------------

This file implements the data structures which house all the data stored in myRedis. RedisStore is a singleton class which exposes relevant methods required by redis cmds.

cmds.cpp (.h)
-------------

This file houses the implementation of redis cmds. These are essentially a thin wrapper to do validation of redis cmds before calling actual methods of RedisStore

type.cpp (.h)
-------------

To send a reply to redis-client, redis-server also needs to serialize output as per RESP. There are multiple [data types](https://redis.io/docs/latest/develop/reference/protocol-spec/#resp-protocol-description) supported in RESP each of which have there own serialization logic. 

This file defines a base class `RObject` from which all fancy types (string, error, integers, bulk string, array) inherit. Each sub-class needs to define it's own `serialize()` method as per RESP.

Arguably some part of RESPParser should have utilized object definitions here, and it might have been nicer to have serialization and deserialization logic in one place. However RESPParser had much more nuances because of validations required before successful deserialization. This is why myRedis has opted to keep them separate.

config.cpp (.h)
---------------

Enables reading up config from the `config.json` file.

Improvements
------------

- Limit number of client connections or explore thread pool architecture
- Use binary protocol to dump in-memory state
- support passing config as an argument
- explore unique data structures optimization in official redis


