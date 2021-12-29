#include <ctime>

#include "headers/database.h"
#include "headers/global_variables.h"
#include "headers/user.h"
#include "headers/product.h"

using namespace std;

int main() {
    // TODO: password should be hashed just after being passed. Proposed place of hashing is user header

    srand((unsigned)time(nullptr));

    /* ----- CREATING TABLE -----*/
    cout << "Creating table..." << endl;
    sqldb.createTable("USERS");
    cout << "Completed\n" << endl;
    User user;

    /* ----- REGISTERING USERS -----*/
    cout << "Register test..." << endl;
    user.registerUser("Aleksander", "Malcew");
    user.registerUser("Josefina", "Neubauer");
    user.registerUser("Khar", "Thoba");
    sqldb.showTable("USERS");
    cout << "Completed\n" << endl;

    /* ----- UPDATING USERS -----*/
    cout << "Updating test..." << endl;
    sqldb.query("UPDATE USERS set LOGIN = 'jneubauer' where ID = 1;");
    sqldb.showTable("USERS");
    cout << "Completed\n" << endl;

    /* ----- DELETING USERS -----*/
    cout << "Deleting test..." << endl;
    for (int i = 0; i < userIndex; i++) sqldb.deleteRow(i, "USERS");
    sqldb.showTable("USERS");
    cout << "Completed\n" << endl;

    /* ----- DROPPING TABLE -----*/
    cout << "Dropping table test..." << endl;
    sqldb.query("DROP TABLE USERS;");
    cout << "Completed\n" << endl;

    /* ----- CREATING TABLE -----*/
    cout << "Creating table..." << endl;
    sqldb.createTable("PRODUCTS");
    cout << "Completed\n" << endl;
    Product product;

    return 0;
}