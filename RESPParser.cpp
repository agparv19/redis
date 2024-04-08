#include "RESPParser.h"


std::string RESPParser::read_from_fd(int n_bytes) {
    char buf[n_bytes];
    ssize_t bytesRead = recv(_read_fd, buf, n_bytes, 0);
    if (bytesRead <= 0) {
        throw SysCallFailure("recv failed!"); //error
    }
    return std::string(buf, bytesRead);
}

/**
 * If there is a valid (CRLF terminated) item in cache,
 * populate 'item' with it and return true.
 * 
 * Returns false otherwise.
*/
bool RESPParser::_cache_has_valid_item(std::string& item) {

    for (int i = 0; i < _read_cache.length(); i++) {

        item += _read_cache[i]; // this is probably bad 
                                // as appending char by char
                                // must be expensive due to re-allocations

        if(item.length() >= 2 &&
           item[item.length()-2] == '\r' &&
           item[item.length()-1] == '\n') {
            
            // Remove the part read 
            _read_cache = _read_cache.substr(i+1);
            return true;
        }
    }
    return false;
}

void RESPParser::_update_cache() {
    _read_cache = read_from_fd(READ_CACHE_MAX);
}

std::string RESPParser::read_next_item() {

    std::string item = "";

    while(!_cache_has_valid_item(item)) {
        if (item.length() > ITEM_LEN_MAX) {
            throw IncorrectProtocol("item length too big!");
        }
        _update_cache();
    }

    return item;
}

/**
 * size_item must look like:
 * "*<number-of-elements>\r\n"
*/
bool RESPParser::_validate_array_size(const std::string& size_item) {

    int len = size_item.length();
    // Must be atleast 4 characters
    if (len < 4) {
        return false;
    }
    // Must begin with *
    if (size_item[0] != '*') {
        return false;
    }
    // Must end with \r\n
    if (size_item[len-1] != '\n' || size_item[len-2] != '\r') {
        return false;
    }
    // Rest should be a number
    for (int i = 1; i <= len-3; i++) {
        if (size_item[i] < '0' || size_item[i] > '9') {
            return false;
        }
    }
    // valid
    return true;
}

/**
 * size_item must look like:
 * $<length>\r\n
*/
bool RESPParser::_validate_bstr_size(const std::string& size_item) {

    int len = size_item.length();
    // Must be atleast 4 characters
    if (len < 4) {
        return false;
    }
    // Must begin with $
    if (size_item[0] != '$') {
        return false;
    }
    // Must end with \r\n
    if (size_item[len-1] != '\n' || size_item[len-2] != '\r') {
        return false;
    }
    // Rest should be a number
    for (int i = 1; i <= len-3; i++) {
        if (size_item[i] < '0' || size_item[i] > '9') {
            return false;
        }
    }
    // valid
    return true;
}


/**
 * Returns true is bstr is terminated with CRLF
*/
bool RESPParser::_validate_crlf(const std::string& bstr) {

    int len = bstr.length();
    if (len < 2) {
        return false;
    }
    return bstr[len-2] == '\r' && bstr[len-1] == '\n';

}

std::vector<std::string> RESPParser::read_new_request(){
    
    // Assumes each RESP request is an array of bulk strings

    // Read size of array in the request 
    std::string arr_size_item = read_next_item();
    if (!_validate_array_size(arr_size_item)){
        throw IncorrectProtocol("Bad array size");
    }
    int size = std::stoi(arr_size_item.substr(1, arr_size_item.length()-3));

    std::vector<std::string> req(size);

    // Read <size> bulk strings
    for (int i = 0; i < size; i++) {

        // Read size of the bulk string
        std::string bstr_size_item = read_next_item();
        if (!_validate_bstr_size(bstr_size_item)){
            throw IncorrectProtocol("Bad bulk string size");
        }
        int bstr_size = std::stoi(bstr_size_item.substr(1, bstr_size_item.length()-3));

        if (bstr_size == -1) {
            // null bulk string
            req[i] = NULL_BULK_STRING;
            continue;
        }
        if (bstr_size < -1) {
            throw IncorrectProtocol("Bulk string size < -1");
        }

        // Read the bulk string
        std::string bstr_item = read_next_item();
        if (!_validate_crlf(bstr_item)) {
            throw IncorrectProtocol("Bulk string not terminated by CRLF");
        }

        std::string bstr = bstr_item.substr(0, bstr_item.length()-2);
        if (bstr.length() != bstr_size) {
            throw IncorrectProtocol("Bulk string size does not match");
        }

        req[i] = bstr;
    }

    return req;
}