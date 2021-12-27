#pragma once

#include <string>
#include <algorithm>


#include "database.h"
#include "global_variables.h"
#include "aux_functions.h"

using std::string;
using std::transform;
using std::tolower;

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
    ~User() {
        free(selfLogin);
        free(selfPassword);
        free(selfEmail);};
    void registerUser(string firstName, const string& lastName) {

        string login = firstName[0] + lastName;
        transform(login.begin(), login.end(), login.begin(), [](unsigned char c){return tolower(c);});
        string email = login + "@company.com";

        selfID = userIndex++;
        strcpy(selfLogin, login.data());
        strcpy(selfPassword, generatePassword(8).data());
        strcpy(selfEmail, email.data());
        sqldb.insertData(selfID, selfLogin, selfPassword, selfEmail);
    }
};

class Admin: public User {
private:
    void addUser() {}
    void blockUser() {}
    void deleteUser() {}
    void modifyUser(){}
};