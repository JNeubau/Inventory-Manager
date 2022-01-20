#include "headers/interface.h"
#include "headers/user.h"
#include "headers/product.h"
#include "headers/global_variables.h"

void Interface::run() {
    /* runs the user interface in main module */

    init();
    loop();
}

void Interface::init() {
    /* performs startup checks and prompts sign form */

    // if there is no admin account in the database, ask to create one
    if (!sqldb.exists("USERS", "IS_STAFF", 1)) {
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

    // if there is at least one user in the database, allow to login
    if (sqldb.anyExists("USERS")) {
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

    // there is no user in the database, do not allow to login
    } else {
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

[[noreturn]] void Interface::loop() {
    /* program main loop */

    string command;
    while (true) {
        if (globalUser->isAdmin()) {
            // if current user have administrative privileges, color username with blue
            cout << "\033[1;34m" << globalUser->getLogin() << "\033[0m> ";
        } else {
            cout << globalUser->getLogin() << "> ";
        }
        // TODO [Interface::loop()]: implement check if passed input is not empty
        cin >> command;
        commands(command);
    }
}

void Interface::commands(string command) {
    /* executes passed command as string */

    // Due to lack of time I've created simple 'if' block, because more sophisticated solution (like map) does not work
    // ouf-of-the-box and need a lot of work. ~AM
    // TODO [Interface::commands()]: implement cleaner solution to the command management

    /* --------------------- USER COMMANDS --------------------- */
    // test command to check if user and admin can both use User's methods
    if (command == "test") {
        globalUser->test();
        return;
    }
    // prints help for standard user
    if ((!globalUser->isAdmin()) && (command == "help")) {

        cout << "\tGeneral Commands:"<< endl;
        cout << "test - invokes test function" << endl;
        cout << "help - print this help message"<< endl;
        cout << "exit - close the program" << endl;
        // menu for products
        cout << "\tProducts MENU:"<< endl;
        cout << "new - add new product"<< endl;
        cout << "remove - delete existing product based on it's name"<< endl;
        cout << "modify - modify existing product"<< endl;
        cout << "clear - delete whole table (not recommended)"<< endl;
        cout << "show - show information about one product" << endl;
        cout << "importAll - creat a file with all product's data" << endl;
        cout << "importBarcodes - creat a file with product's name and barcode" << endl;
        // end menu for products

        return;
    }

    /* --------------------- PRODUCT COMMANDS --------------------- */
    // adds new product to the database
    if ((!globalUser->isAdmin()) && (command == "new")) {
        newProduct();
    }
    // removes product from the database
    if ((!globalUser->isAdmin()) && (command == "remove")) {
        if (sqldb.anyExists("PRODUCTS")) {
            string columnName;
            char *tempColumnName;
            cout << "For which type of value would you like to search?\nNAME || BARCODE" << endl;
            cin >> columnName;
            strcpy(tempColumnName, columnName.data());
            if (strcmp(tempColumnName, "NAME") == 0) {
                cout << "What's the product's name??" << endl;
                string name;
                cin >> name;
                if (sqldb.exists("PRODUCTS", "PRODUCT_NAME", name)) {
                    Product::deleteProduct(name);
                }
            } else if (strcmp(tempColumnName, "BARCODE") == 0) {
                cout << "What's the product's barcode??" << endl;
                int barcode;
                cin >> barcode;
                if (sqldb.exists("PRODUCTS", "BARCODE", barcode)) {
                    Product::deleteProduct(barcode);
                }
            } else {
                cout << "Wrong type of value chosen" << endl;
            }
        } else {
            cout << "There's nothing to remove" << endl;
        }
    }
    // allows to change product's fields
    if ((!globalUser->isAdmin()) && (command == "modify")) {
        cout << "modify function" << endl;
        if (sqldb.anyExists("PRODUCTS")) {
            string productName;
            cout << "Enter current name of the product that you want to modify: ";
            cin >> productName;
            string newName;
            bool exit = false;
            while (!exit) {
                cout << "Which value would you like to modify?" << endl;
                cout << "1.name || 2.quantity || 3.prize || 4.barcode || 5.producer || 6.category || 7.that's all" << endl;
                int number;
                cin >> number;
                switch (number) {
                    case 1:     // name
                        cout << "Enter new name: ";
                        cin >> newName;
                        Product::modifyProduct(productName, newName, "PRODUCT_NAME");
                        productName = newName;
                        break;
                    case 2:     // quantity
                        cout << "Enter new amount: ";
                        long amount;
                        cin >> amount;
                        Product::modifyProduct(productName, amount);
                        break;
                    case 3:     // prize
                        cout << "Enter new prize: ";
                        float prize;
                        cin >> prize;
                        Product::modifyProduct(productName, prize);
                        break;
                    case 4:     // barcode
                        cout << "Enter new barcode: ";
                        int barcode;
                        cin >> barcode;
                        Product::modifyProduct(productName, barcode);
                        break;
                    case 5:     // producer
                        cout << "Enter new maker: ";
                        cin >> newName;
                        Product::modifyProduct(productName, newName, "PRODUCER_NAME");
                        break;
                    case 6:     // category
                        cout << "Enter new category: ";
                        cin >> newName;
                        Product::modifyProduct(productName, newName, "CATEGORY");
                        break;
                    case 7:
                        exit = true;
                        break;
                    default:
                        cout << "Wrong option chosen" << endl;
                        break;
                }
            }
        } else {
            cout << "There's nothing to modify" << endl;
        }
    }
    // drops the previous table and creates a new clear one
    if ((!globalUser->isAdmin()) && (command == "clear")) {
        sqldb.clearDB();
    }
    // shows information about one product
    if ((!globalUser->isAdmin()) && (command == "show")) {
        string name;
        cout << "Which products detail would you like to see\nName: ";
        cin >> name;
        char *tempName = (char *) (malloc(sizeof(char)));
        strcpy(tempName, name.data());

        int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", tempName);
        cout <<id << endl;
        sqldb.showRow("PRODUCTS", id);
    }
    // creates a file 'Database.txt' in main folder with all the data from the products database
    if ((!globalUser->isAdmin()) && (command == "importAll")) {
        sqldb.dbToFile();
    }
    // creates a file with names and corresponding barcodes
    if ((!globalUser->isAdmin()) && (command == "importBarcodes")) {
        sqldb.barcodesFile();
    }

    /* --------------------- ADMIN COMMANDS --------------------- */
    // adds user into the database
    if ((globalUser->isAdmin()) && (command == "add")) {
        // TODO [add command]: implement check if passed input is not empty
        string login, password, email;
        bool is_staff;
        cout << "Create new account ->"<< endl;
        cout << "login: ";
        cin >> login;
        if (!sqldb.exists("USERS", "LOGIN", login)) {
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
    // deletes user from the database
    if ((globalUser->isAdmin()) && (command == "delete")) {
        // TODO [delete command]: implement check if passed input is not empty
        string login;
        cout << "Delete account ->"<< endl;
        cout << "login: ";
        cin >> login;
        if (sqldb.exists("USERS", "LOGIN", login)) {
            adminUser->deleteUser(login);
        } else {
            cout << "\033[1;31mThere is no such user as '" << login <<"'\033[0m" << endl;
        }
        return;
    }
    // edits the existing user
    if ((globalUser->isAdmin()) && (command == "edit")) {
        // TODO [modify command]: implement check if passed input is not empty
        string login;
        cout << "Edit account ->"<< endl;
        cout << "login: ";
        cin >> login;
        if (sqldb.exists("USERS", "LOGIN", login)) {
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
                            adminUser->modifyUser(login, "ID", newValue);
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
                        adminUser->modifyUser(login, "LOGIN", newValue);
                        break;
                    }
                } else if (flag[0] == 'p' || flag[0] == 'P') {
                    string newValue;
                    cout << "new value: ";
                    cin >> newValue;
                    adminUser->modifyUser(login, "PASSWORD", newValue);
                    break;
                } else if (flag[0] == 'e' || flag[0] == 'E') {
                    string newValue;
                    cout << "new value: ";
                    cin >> newValue;
                    adminUser->modifyUser(login, "EMAIL", newValue);
                    break;
                } else if (flag[0] == 'a' || flag[0] == 'A') {
                    if (login == adminUser->getLogin()) {
                        cout << "\033[1;31mCannot modify active account admin permission\033[0m" << endl;
                        continue;
                    } else {
                        char* chrLogin = &login[0];
                        bool isStaff = sqldb.isAdmin(chrLogin);
                        adminUser->modifyUser(login, "IS_STAFF", !isStaff);
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
    // prints help for admin
    if ((globalUser->isAdmin()) && (command == "help")) {
        cout << "add - create new user account" << endl;
        cout << "delete - delete existing user account" << endl;
        cout << "edit - edit existing user account" << endl;
        cout << "help - print this help message"<< endl;
        cout << "exit - close the program" << endl;
        return;
    }

    /* -------------------- GLOBAL COMMANDS -------------------- */
    // kills the program
    if (command == "exit") {
        exit(1);
    }
    // if no command was executed, give user a tip
    cout << "Command not found, type 'help' for more information" << endl;
}

void Interface::registerUser(bool isStaff) {
    /* perform user registration*/

    // TODO [Interface::registerUser()]: implement check if passed input is not empty
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

void Interface::newProduct() {
    Product product;
    string productName, producerName, categoryName;
    long quantity;
    float prize;
    int barcode;
    cout << "Pass the data of new product:" << endl;
    cout << "\tProduct's name: ";
    cin >> productName;
    cout << "\tProducer: ";
    cin >> producerName;
    cout << "\tCategory of the product: ";
    cin >> categoryName;
    cout << "\tAmount: ";
    cin >> quantity;
    cout << "\tPrize for unit: ";
    cin >> prize;
    // TODO: make sure barcode has 8 digits
    cout << "\tBarcode for the product (must have 8 numbers): ";
    cin >> barcode;
    product.addNewProduct(productName, quantity, prize, barcode, producerName, categoryName);
    cout << std::flush;
    // TODO: Flushing not working?
}

void Interface::loginUser() {
    /* perform user login and exits the program, if user made too many incorrect attempts */

    // TODO [Interface::login()]: implement check if passed input is not empty
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