#pragma once

#include <string>
using namespace std;

class User {
public:
    // TODO:
    //  1) rename the User variables,
    //  2) create appropriate function to pass the variables and protect them (make them private!)
    //  3) when the database will work, implement isActive variable to check if user is logged into the system
    string selfLogin;
    string selfPassword;
    string selfEmail;
    // bool isActive;

public:
    User(string login, string password, string email) {
        selfLogin = login;
        selfPassword = password;
        selfEmail = email;
    }
};