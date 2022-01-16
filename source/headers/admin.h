#pragma once

#include "user.h"

class Admin: public User {
public:
    Admin() = default;

    void addUser(string login, string password, string email, bool isStaff);

    void deleteUser(string login);

    void modifyUser(string login, string field, string newValue);

    void modifyUser(string login, string field, int newValue);

    void dropDatabase(char* table);
};