#include "headers/interface.h"
#include "headers/user.h"
#include "headers/global_variables.h"

void Interface::run() {
    init();
    loop();
}

void Interface::init() {
    if (!sqldb.exists("USERS", "is_staff", 1)) {
        cout << "\033[1;31mNo admin account found!\033[0m" << endl;
        while (true) {
            cout << "Create admin account now? [Y/n]: ";
            string flag;
            cin >> flag;
            if (flag[0] == 'y' || flag[0] == 'Y'){
                registerUser(true);
                break;
            } else if (flag[0] == 'n' || flag[0] == 'N') {
                break;
            } else {
                cout << "Unknown mode, please try again" << endl;
                continue;
            }
        }
    }

    if (sqldb.anyExists("USERS")) {  // there is at least one user in database
        cout << "Select action:\n\t[l] login\n\t[r] register\n\t[x] exit" << endl;
        while (true) {
            cout << "? ";
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
            cout << "? ";
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

void Interface::loop() {
    string command;
    while (true) {
        if (globalUser->isAdmin()) {
            cout << "\033[1;34m" << globalUser->getLogin() << "\033[0m> ";
        } else {
            cout << globalUser->getLogin() << "> ";
        }
        cin >> command;
        commands(command);
    }
}

void Interface::commands(string command) {

    /* --------------------- USER COMMANDS --------------------- */
    if (command == "test") {
        globalUser->test();
        return;
    }

    if ((!globalUser->isAdmin()) && (command == "help")) {
        cout << "test - invokes test function" << endl;
        cout << "help - print this help message"<< endl;
        cout << "exit - close the program" << endl;
        return;
    }

    /* --------------------- ADMIN COMMANDS --------------------- */
    if ((globalUser->isAdmin()) && (command == "add")) {
        // TODO [add command]: implement check if passed input is not empty
        string login, password, email;
        bool is_staff;
        cout << "Create new account ->"<< endl;
        cout << "login: ";
        cin >> login;
        if (!sqldb.exists("USERS", "login", login)) {
            cout << "email: ";
            cin >> email;
            cout << "password: ";
            cin >> password;
            while (true) {
                cout << "is admin? [y/n]: ";
                string flag;
                cin >> flag;
                if (flag[0] == 'y' || flag[0] == 'Y'){
                    is_staff = true;
                    break;
                } else if (flag[0] == 'n' || flag[0] == 'N') {
                    is_staff = false;
                    break;
                } else {
                    cout << "Unknown mode, please try again" << endl;
                    continue;
                }
            }
            adminUser->addUser(login, password, email, is_staff);
        } else {
            cout << "\033[1;31mThere already is an user with login '" << login <<"'\033[0m" << endl;
        }
        return;
    }

    if ((globalUser->isAdmin()) && (command == "delete")) {
        // TODO [delete command]: implement check if passed input is not empty
        string login;
        cout << "Delete account ->"<< endl;
        cout << "login: ";
        cin >> login;
        if (sqldb.exists("USERS", "login", login)) {
            adminUser->deleteUser(login);
        } else {
            cout << "\033[1;31mThere is no such user as '" << login <<"'\033[0m" << endl;
        }
        return;
    }

    if ((globalUser->isAdmin()) && (command == "edit")) {
        // TODO [modify command]: implement check if passed input is not empty
        string login;
        cout << "Edit account ->"<< endl;
        cout << "login: ";
        cin >> login;
        if (sqldb.exists("USERS", "login", login)) {
            cout << "Select field to edit: \n\t[i] id\n\t[l] login\n\t[p] password\n\t[e] email\n\t[a] admin permission\n\n\t[x] cancel" << endl;
            while (true) {
                cout << "? ";
                string flag;
                cin >> flag;
                if (flag[0] == 'i' || flag[0] == 'I') {
                    if (login == adminUser->getLogin()) {
                        cout << "\033[1;31mCannot modify active account id\033[0m" << endl;
                        continue;
                    } else {
                        int newValue;
                        cout << "new id: ";
                        cin >> newValue;
                        if (!sqldb.exists("USERS", "ID", newValue)) {
                            adminUser->modifyUser(login, "id", newValue);
                            break;
                        } else {
                            cout << "\033[1;31mCannot modify id, user with given id already exists\033[0m" << endl;
                            continue;
                        }
                    }
                } else if (flag[0] == 'l' || flag[0] == 'L') {
                    if (login == adminUser->getLogin()) {
                        cout << "\033[1;31mCannot modify active account login\033[0m" << endl;
                        continue;
                    } else {
                        string newValue;
                        cout << "new value: ";
                        cin >> newValue;
                        adminUser->modifyUser(login, "login", newValue);
                        break;
                    }
                } else if (flag[0] == 'p' || flag[0] == 'P') {
                    string newValue;
                    cout << "new value: ";
                    cin >> newValue;
                    adminUser->modifyUser(login, "password", newValue);
                    break;
                } else if (flag[0] == 'e' || flag[0] == 'E') {
                    string newValue;
                    cout << "new value: ";
                    cin >> newValue;
                    adminUser->modifyUser(login, "email", newValue);
                    break;
                } else if (flag[0] == 'a' || flag[0] == 'A') {
                    if (login == adminUser->getLogin()) {
                        cout << "\033[1;31mCannot modify active account admin permission\033[0m" << endl;
                        continue;
                    } else {
                        char* chrLogin = &login[0];
                        bool isStaff = sqldb.isAdmin(chrLogin);
                        adminUser->modifyUser(login, "is_staff", !isStaff);
                        break;
                    }
                } else if (flag[0] == 'x' || flag[0] == 'X') {
                    break;
                } else {
                    cout << "Unknown mode, please try again" << endl;
                    continue;
                }
            }
        } else {
            cout << "\033[1;31mThere is no such user as '" << login <<"'\033[0m" << endl;
        }
        return;
    }

    if ((globalUser->isAdmin()) && (command == "help")) {
        cout << "add - create new user account" << endl;
        cout << "delete - delete existing user account" << endl;
        cout << "edit - edit existing user account" << endl;
        cout << "help - print this help message"<< endl;
        cout << "exit - close the program" << endl;
        return;
    }

    if (command == "exit") {
        exit(1);
    }

    cout << "Command not found, type 'help' for more information" << endl;
}

void Interface::registerUser(bool isStaff) {
    // TODO [registerUser()]: implement check if passed input is not empty
    string firstName;
    string lastName;
    cout << "Sign up ->" << endl;
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
    cout << "Sign in ->" << endl;
    int currentAttempt = 1;
    while (true) {
        cout << "login: ";
        cin >> login;
        cout << "password: ";
        cin >> password;
        if (globalUser->loginUser(login, password)) {
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