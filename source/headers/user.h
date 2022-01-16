#pragma once

#include <algorithm>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

class User {
protected:
    // TODO [fields]: rename the User variables,
    int selfID;
    char *selfLogin = (char *)(malloc(sizeof(char)));
    char *selfPassword = (char *)(malloc(sizeof(char)));
    char *selfEmail = (char *)(malloc(sizeof(char)));
    bool selfIsStaff;

public:
    User() = default;;

    ~User();

    void registerUser(string firstName, const string& lastName, bool isStaff);

    bool loginUser(string login, string password);

    bool isAdmin();

    string getLogin();

    virtual void test();
};