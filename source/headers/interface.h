#pragma once

#include <map>
#include <iostream>
#include <string>

using std::map;
using std::string;

class Interface {
private:
    map<string, void (*)()> commands;
    void init();

    // void loop();

    void registerUser(bool isStaff);

    void loginUser();


public:
    Interface() = default;;
    void run();
};