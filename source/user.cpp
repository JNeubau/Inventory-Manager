#include "headers/user.h"
#include "headers/aux_functions.h"
#include "headers/global_variables.h"

User::~User() {
    // TODO [destructor]: Verify, if fields's memory shouldn't be freed in the deconstructor
}

void User::registerUser(string firstName, const string& lastName, bool isStaff) {
    /* converts passed strings to respective datatype, generates login and password, performs a query */

    string login = firstName[0] + lastName;
    std::transform(login.begin(), login.end(), login.begin(), [](unsigned char c){return std::tolower(c);});
    selfID = sqldb.nextId("USERS");
    int id = sqldb.find("USERS", "LOGIN", &login[0]);

    // if generated login is already present in the database, append id
    if (sqldb.exists("USERS", "ID", id)) login = login + to_string(selfID);

    // generate User object data
    string email = login + domain;
    selfLogin = &login[0];
    selfPassword = &generatePassword(passwordLength)[0];
    selfEmail = &email[0];

    sqldb.insertData(selfID, selfLogin, selfPassword, selfEmail, isStaff);

    // print out the credentials
    cout << "\nAccount created:" << endl;
    cout << "\tlogin: \033[1;34m" << selfLogin << "\033[0m, \n\tpass: \033[1;34m" << selfPassword << "\033[0m\n" << endl;
}

bool User::loginUser(string login, string password) {
    /* fills user's fields and performs authentication query, returns boolean */

    strcpy(selfLogin, login.data());
    strcpy(selfPassword, password.data());
    return sqldb.authenticate(selfLogin, selfPassword);
}

bool User::isAdmin() {
    /* returns whether user is administrator */

    selfIsStaff = sqldb.isAdmin(selfLogin);
    return selfIsStaff;
}

string User::getLogin() {
    /* returns login */

    return selfLogin;
}

void User::test() {
    /* test function to check if both User and Admin can use this method */

    cout << "this is a test function" << endl;
}