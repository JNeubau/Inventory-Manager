#include "headers/user.h"
#include "headers/aux_functions.h"
#include "headers/global_variables.h"

User::~User() {
    /* DECONSTRUCTOR */

    // free the memory
    free(selfLogin);
    free(selfPassword);
    free(selfEmail);
}

void User::registerUser(string firstName, const string &lastName) {
    /* function used to register the user into the database */

    string login = firstName[0] + lastName;
    std::transform(login.begin(), login.end(), login.begin(), [](unsigned char c){return std::tolower(c);});
    string email = login + "@company.com";

    selfID = userIndex++;
    strcpy(selfLogin, login.data());
    strcpy(selfPassword, generatePassword(8).data());
    strcpy(selfEmail, email.data());
    sqldb.insertData(selfID, selfLogin, selfPassword, selfEmail);
}

void User::login() {
    /* function used to authenticate user with data stored in database */

    char lgin[32];
    char pswd[128];
    int attempts = 1;
    while (true) {
        cout << "login: ";
        cin >> lgin;
        cout << "password: ";
        cin >> pswd;
        bool flag = sqldb.login(lgin, pswd);
        if (flag) {
            cout << "login correct";
            break;
        } else {
            if (attempts == loginAttempts) {
                cout << "\033[1;31mtoo many incorrect attempts, exiting\033[0m\n";
                exit(1);
            }
            cout << "\033[1;31mincorrect login or password, please try again\033[0m\n";
            ++attempts;
        }
    }
}
