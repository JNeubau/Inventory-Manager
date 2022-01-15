#include "headers/interface.h"
#include "headers/user.h"
#include "headers/global_variables.h"
#include "headers/database.h"

using std::cout;
using std::endl;

void Interface::run() {
    init();
    // loop();
}

void Interface::init() {
    if (!sqldb.exists("USERS", "is_staff", 1)) {
        cout << "\033[1;31mNo admin account found!\033[0m" << endl;
        cout << "Create admin account now? [Y/n]: ";
        while (true) {
            string flag;
            cin >> flag;
            if (flag[0] == 'y' || flag[0] == 'Y'){
                registerUser(true);
                break;
            } else if (flag[0] == 'n' || flag[0] == 'N') {
                break;
            } else {
                cout << "Unknown mode, please try again [Y/n]: ";
                continue;
            }
        }
    }

    if (sqldb.exists("USERS", "ID", 0)) {  // there is at least one user in database
        cout << "Select action:\n\t[l] login\n\t[r] register\n\t[x] exit" << endl;
        while (true) {
            cout << "> ";
            string flag;
            cin >> flag;
            if (flag[0] == 'l' || flag[0] == 'L'){
                loginUser();
                break;
            } else if (flag[0] == 'r' || flag[0] == 'R') {
                registerUser(false);
                loginUser();
                break;
            } else if (flag[0] == 'x' || flag[0] == 'X') {
                exit(1);
            } else {
                cout << "Unknown mode, please try again" << endl;
                continue;
            }
        }
    } else {  // there is no user in the database
        cout << "Select action:\n\t[r] register\n\t[x] exit" << endl;
        while (true) {
            cout << "> ";
            string flag;
            cin >> flag;
            if (flag[0] == 'r' || flag[0] == 'R') {
                registerUser(false);
                loginUser();
                break;
            } else if (flag[0] == 'x' || flag[0] == 'X') {
                exit(1);
            } else {
                cout << "Unknown mode, please try again" << endl;
                continue;
            }
        }
    }
}

void Interface::registerUser(bool isStaff) {

    // TODO [registerUser()]: implement check if passed input is not empty
    string firstName;
    string lastName;
    cout << "first name: ";
    cin >> firstName;
    cout << "last name: ";
    cin >> lastName;
    User newUser;
    newUser.registerUser(firstName, lastName, isStaff);
}

void Interface::loginUser() {

    // TODO [login()]: implement check if passed input is not empty
    string login;
    string password;
    int currentAttempt = 1;
    while (true) {
        cout << "login: ";
        cin >> login;
        cout << "password: ";
        cin >> password;
        if (globalUser.loginUser(login, password)) {
            cout << "Hello, " << login << endl;
            break;
        } else {
            if (currentAttempt++ == loginAttempts) {
                cout << "\033[1;31mToo many incorrect attempts, exiting\033[0m" << endl;
                exit(1);
            }
            cout << "\033[1;31mIncorrect login or password, please try again\033[0m" << endl;
        }
    }
}