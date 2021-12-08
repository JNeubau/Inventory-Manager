#pragma once

#include <string>

#include "database.h"
#include "init.h"

class User {
private:
    // TODO:
    //  1) rename the User variables,
    //  2) when the database will work, implement isActive variable to check if user is logged into the system
    char *selfLogin = nullptr;
    char *selfPassword = nullptr;
    char *selfEmail = nullptr;
    // bool isActive;

public:
    User() = default;;
    ~User() {
        free(selfLogin);
        free(selfPassword);
        free(selfEmail);
    };
    void registerUser(char* login, char* password, char* email) {
        selfLogin = login;
        selfPassword = password;
        selfEmail = email;
        sqldb.insertData(selfLogin, selfPassword, selfEmail);
    }
};