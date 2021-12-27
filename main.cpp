#include "headers/database.h"
#include "headers/global_variables.h"
#include "headers/user.h"

using namespace std;

int main() {
    // TODO: password should be hashed just after being passed. Proposed place of hashing is user header

    /* ----- CREATING TABLE -----*/
    cout << "Creating table..." << endl;
    sqldb.createTable("USERS");
    cout << "Completed\n" << endl;
    User user;

    /* ----- REGISTERING USERS -----*/
    cout << "Register test..." << endl;
    user.registerUser(userIndex++, "amalcew", "qwerty", "amalcew@protonmail.com");
    user.registerUser(userIndex++, "fenix12", "hjklaDfeaw", "jneubauer@gmail.com");
    user.registerUser(userIndex++, "kthoba", "q1w2e3r4", "kthoba@gmail.com");
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

    return 0;
}