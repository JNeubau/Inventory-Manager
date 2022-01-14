#pragma once

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

using std::cout;
using std::cin;
using std::string;

class User {
private:
    // TODO:
    //  1) rename the User variables,
    //  2) when the database will work, implement isActive variable to check if user is logged into the system
    int selfID;
    char *selfLogin = (char *)(malloc(sizeof(char)));
    char *selfPassword = (char *)(malloc(sizeof(char)));
    char *selfEmail = (char *)(malloc(sizeof(char)));
    // bool isActive;

public:
    User() = default;;

    ~User();

    void registerUser(string firstName, const string& lastName);

    void login();
};

class Admin: public User {
public:  // TODO: methods should be at least protected
    Admin() = default;

    void addUser(char* login, char* password, char* email);

    void blockUser();

    void deleteUser(int index);

    void deleteUser(char* login);

    void modifyUser(char* login, char* field, char* new_value);

    void dropDatabase(char* table);
};