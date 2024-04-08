#include "common.h"

namespace redis {

    class RObject {
    
    public:
        virtual ~RObject() {};
        virtual std::string prefix() = 0;
        virtual std::string serialize() = 0;
        static std::string CRLF;

    };

    class SimpleString : public RObject {
    
    public:
        SimpleString(const std::string& input) {
            str = input;
        }
        std::string prefix() override {
            return "+";
        }
        std::string serialize() override {
            return prefix() + str + CRLF;
        }
    private:
        std::string str;

    };

    class Error : public RObject {
    
    public:
        Error(const std::string& input) {
            str = input;
        }
        std::string prefix() override {
            return "-";
        }
        std::string serialize() override {
            return prefix() + str + CRLF;
        }
    private:
        std::string str;

    };

    class Integer : public RObject {
    
    public:
        Integer(int input) {
            val = input;
        }
        std::string prefix() override {
            return ":";
        }
        std::string serialize() override {
            return prefix() + std::to_string(val) + CRLF;
        }
    private:
        int val;

    };

    class BulkString : public RObject {
    
    public:
        BulkString(const std::string& input) {
            str = input;
        }
        std::string prefix() override {
            return "$";
        }
        std::string serialize() override {
            return prefix() + std::to_string(str.size()) + CRLF
                            + str + CRLF;
        }
    private:
        std::string str;
    };

    class NullString : public RObject {
    
    public:
        NullString() {
            str = "-1";
        }
        std::string prefix() override {
            return "$";
        }
        std::string serialize() override {
            return prefix() + str + CRLF;
        }
    private:
        std::string str;
    };

    class Array : public RObject {
    
    public:
        Array() {}
        std::string prefix() override {
            return "*";
        }
        std::string serialize() override {
            std::string res = prefix() + std::to_string(array.size()) + CRLF;
            for (const auto& it : array) {
                res += it->serialize();
            }
            return res;
        }
        void add_element(std::unique_ptr<RObject> robj) {
            array.emplace_back(std::move(robj));
        }
        Array(const Array&) = delete;
        Array& operator=(const Array&) = delete;
    private:
        std::vector<std::unique_ptr<RObject>> array;
    };
    
}

