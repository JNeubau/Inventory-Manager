#pragma once

#include <string>

#include "database.h"
#include "global_variables.h"

class User {
private:
    // TODO:
    //  1) rename the User variables,
    //  2) when the database will work, implement isActive variable to check if user is logged into the system
    int selfID{};
    char *selfLogin = nullptr;
    char *selfPassword = nullptr;
    char *selfEmail = nullptr;
    // bool isActive;

public:
    User() = default;;
    ~User() {
        free(reinterpret_cast<void *>(selfID));
        free(selfLogin);
        free(selfPassword);
        free(selfEmail);
    };
    void registerUser(int id, char* login, char* password, char* email) {
        selfID = id;
        selfLogin = login;
        selfPassword = password;
        selfEmail = email;
        sqldb.insertData(selfID, selfLogin, selfPassword, selfEmail);
    }
};