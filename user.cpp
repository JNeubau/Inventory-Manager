#include "headers/user.h"
#include "headers/aux_functions.h"
#include "headers/global_variables.h"

User::~User() {
    /* DECONSTRUCTOR */
}

void User::registerUser(bool isStaff) {
    /* function used to register the user into the database */

    // TODO:
    //  1) registration - implement check if passed input is not empty
    //  2) registration - rewrite the input part into the interface, this function should work on passed parameters only
    string firstName;
    string lastName;
    cout << "first name: ";
    cin >> firstName;
    cout << "last name: ";
    cin >> lastName;
    string login = firstName[0] + lastName;
    std::transform(login.begin(), login.end(), login.begin(), [](unsigned char c){return std::tolower(c);});
    string email = login + "@company.com";
    selfID = sqldb.nextId("USERS");
    // TODO: WTF, why I can't use strcpy below??
    selfLogin = &login[0];
    selfPassword = &generatePassword(8)[0];
    selfEmail = &email[0];
    sqldb.insertData(selfID, selfLogin, selfPassword, selfEmail, isStaff);
    cout << "pass: \033[1;34m" << selfPassword << "\033[0m"<<endl;
}

void User::login() {
    /* function used to authenticate user with data stored in database */

    // TODO:
    //  1) login - implement check if passed input is not empty
    //  2) login - rewrite the input part into the interface, this function should work on passed parameters only

    string login;
    string password;
    int currentAttempt = 1;
    while (true) {
        cout << "login: ";
        cin >> login;
        cout << "password: ";
        cin >> password;
        strcpy(selfLogin, login.data());
        strcpy(selfPassword, password.data());
        bool flag = sqldb.login(selfLogin, selfPassword);
        if (flag) {
            cout << "Hello, " << selfLogin << endl;
            break;
        } else {
            if (currentAttempt++ == loginAttempts) {
                cout << "\033[1;31mToo many incorrect attempts, exiting\033[0m" << endl;
                exit(1);
            }
            cout << "\033[1;31mNncorrect login or password, please try again\033[0m" << endl;
        }
    }
}
