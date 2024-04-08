#include "common.h"
#include <vector>
#include <unordered_map>

bool test_have_crlf() {

    std::cout << "Running test_have_crlf..." << std::endl;

    std::unordered_map<std::string, int> inputs = {
        // 1 - true, 0 - false, -1 - IncorrectProtocol
        {"$-1\r\n", 1},
        {"-Error message\r\n", 1},
        {"*1\r\n$4\r\nping\r\n", 1},
        {"+hello world", 0},
        {"\r", 0},
        {"\r+", -1},
    };

    for (auto it = inputs.begin(); it != inputs.end(); it++) {
        try {
            bool output = have_crlf((it->first).c_str(), (it->first).size());
            if (output != (bool)it->second) {
                std::cout << "failed for " << it->first << std::endl;
                return false;
            }
        } catch (const IncorrectProtocol& e) {
            if (it->second != -1) {
                std::cout << "failed for " << it->first << std::endl;
                return false;
            }
        }
    }       
    std::cout << "passed" << std::endl;
    return true; // success

}


int main() {
    test_have_crlf();
}