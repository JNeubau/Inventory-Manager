#include "headers/user.h"
#include "headers/aux_functions.h"
#include "headers/global_variables.h"

User::~User() {
    // TODO [destructor]: Verify, if fields's memory shouldn't be freed in the deconstructor
}

void User::registerUser(string firstName, const string& lastName, bool isStaff) {
    // TODO [registerUser()]: password should be stored as hashed
    string login = firstName[0] + lastName;
    std::transform(login.begin(), login.end(), login.begin(), [](unsigned char c){return std::tolower(c);});
    selfID = sqldb.nextId("USERS");
    char* chrLogin = &login[0];  // TODO: refactor not to user char array
    int id = sqldb.find("USERS", "login", chrLogin);
    if (sqldb.exists("USERS", "ID", id)) {
        login = login + to_string(selfID);
    }
    string email = login + "@company.com";
    selfLogin = &login[0];
    selfPassword = &generatePassword(8)[0];
    selfEmail = &email[0];
    sqldb.insertData(selfID, selfLogin, selfPassword, selfEmail, isStaff);
    cout << "\nAccount created:" << endl;
    cout << "\tlogin: \033[1;34m" << selfLogin << "\033[0m, \n\tpass: \033[1;34m" << selfPassword << "\033[0m\n" << endl;
}

bool User::loginUser(string login, string password) {
    strcpy(selfLogin, login.data());
    strcpy(selfPassword, password.data());
    return sqldb.authenticate(selfLogin, selfPassword);
}

bool User::isAdmin() {
    selfIsStaff = sqldb.isAdmin(selfLogin);
    return selfIsStaff;
}

string User::getLogin() {
    return selfLogin;
}

void User::test() {
    cout << "this is a test function" << endl;
}