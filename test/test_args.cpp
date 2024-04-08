#include <bits/stdc++.h>
#include <string>

void read_request(int fd, int &argc, char** &argv){
    argc = fd+1;
    argv = new char*[argc];
    for (int i=0; i<argc; i++) {
        //char ans[] = "parv";
        argv[i] = new char[5];
        std::strcpy(argv[i], std::string("parv").c_str());
    }
}

int main() {
    int argc;
    char** argv; // array of char*
    read_request(2, argc, argv);
    for (int i=0; i<argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    std::string test = "parv";

    for (int i=0; i<test.length(); i++) {
        std::cout<<test[i]<<"$"<<std::endl;
    }

    char buf[] = {'p', 'a'};
    std::string str(buf);

    for (int i=0; i<str.length(); i++) {
        std::cout<<str[i]<<"*"<<std::endl;
    }
}