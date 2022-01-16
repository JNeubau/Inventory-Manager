#pragma once

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Interface {
private:
    void init();

    [[noreturn]] void loop();

    void commands(string command);

    void registerUser(bool isStaff);

    void loginUser();

public:
    Interface() = default;;
    void run();
};