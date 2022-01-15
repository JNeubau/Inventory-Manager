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
    // TODO [fields]:
    //  1) rename the User variables,
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
};

class Admin: public User {
public:  // TODO: methods should be at least protected
    Admin() = default;

    void addUser(char* login, char* password, char* email, bool isStaff);

    void blockUser();

    void deleteUser(int index);

    void deleteUser(char* login);

    void modifyUser(char* login, char* field, char* new_value);

    void dropDatabase(char* table);
};