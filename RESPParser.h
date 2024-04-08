#pragma once
#include "common.h"

#define NULL_BULK_STRING "NULL"
#define READ_CACHE_MAX 8192
#define ITEM_LEN_MAX 536870912 // 512 MB

class RESPParser {

private:
    int _read_fd = -1; 
    std::string _read_cache = "";


protected:
    bool _validate_array_size(const std::string& size_item);
    bool _validate_bstr_size(const std::string& size_item);
    bool _validate_crlf(const std::string& bstr);
    bool _cache_has_valid_item(std::string& item);
    void _update_cache();

    /**
     * Read upto n_bytes from fd
    */
    std::string read_from_fd(int n_bytes);

    /**
     * Returns next item on _read_fd
     * An item terminates in /r/n
    */
    std::string read_next_item();


public:

    RESPParser(int fd) {
        _read_fd = fd;
        _read_cache = "";
    }

    /**
     * Read a new request from a _read_fd
     * Returns the request as a vector of string 
     * with first element being command name
    */
    std::vector<std::string> read_new_request();
};