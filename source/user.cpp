#include "headers/user.h"
#include "headers/aux_functions.h"
#include "headers/global_variables.h"

User::~User() {
    /* DECONSTRUCTOR */

    // TODO [deconstructor]: Verify, if fields's memory shouldn't be freed in the deconstructor
}

void User::registerUser(string firstName, const string& lastName, bool isStaff) {
    /* function used to register the user into the database */
    // TODO [registerUser()]:
    //  1) password should be stored as hashed
    //  2) implement verification if login does not already exist in the database

    string login = firstName[0] + lastName;
    std::transform(login.begin(), login.end(), login.begin(), [](unsigned char c){return std::tolower(c);});
    string email = login + "@company.com";
    selfID = sqldb.nextId("USERS");
    selfLogin = &login[0];
    selfPassword = &generatePassword(8)[0];
    selfEmail = &email[0];
    sqldb.insertData(selfID, selfLogin, selfPassword, selfEmail, isStaff);
    cout << "\nAccount created:" << endl;
    cout << "\tlogin: \033[1;34m" << selfLogin << "\033[0m, \n\tpass: \033[1;34m" << selfPassword << "\033[0m\n"<<endl;
}

bool User::loginUser(string login, string password) {
    /* function used to authenticate user with data stored in database */

    strcpy(selfLogin, login.data());
    strcpy(selfPassword, password.data());
    return sqldb.login(selfLogin, selfPassword);
}
