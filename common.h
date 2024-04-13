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


#define PORT 2000

#define MAX_PACKET_SIZE 4096

void die(const char* msg);

void msg(const char *msg);

void print(const char *msg);

bool have_crlf(const char* buf, int len);

int recv_exactly(int fd, char* buf, size_t n_bytes);

int write_exactly(int fd, const char* buf, size_t n_bytes);

int recv_one_packet(int fd, char* buf);

int send_one_packet(int fd, const char* buf);

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

