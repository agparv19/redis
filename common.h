#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <boost/asio.hpp>
#include <chrono>

void die(const char* msg);

int recv_exactly(int fd, char* buf, size_t n_bytes);

int write_exactly(int fd, const char* buf, size_t n_bytes);

std::string to_lower(const std::string& str);

class IncorrectProtocol : public std::runtime_error {
public:
    // Constructor with a message
    explicit IncorrectProtocol(const std::string& message) : std::runtime_error(message) {}
};

class SysCallFailure : public std::runtime_error {
public:
    // Constructor with a message
    explicit SysCallFailure(const std::string& message) : std::runtime_error(message) {}
};

class RedisServerError : public std::runtime_error {
public:
    // Constructor with a message
    explicit RedisServerError(const std::string& message) : std::runtime_error(message) {}
};
