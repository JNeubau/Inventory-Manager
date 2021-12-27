#pragma once

#include <string>

using std::string;

const char alphanum[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int string_length = sizeof(alphanum)-1;

string generatePassword(int length) {
    string password;
    for (int i = 0; i < length; i++) password += alphanum[rand()% string_length];
    return password;
}