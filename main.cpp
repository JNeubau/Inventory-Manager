#include <ctime>

#include "headers/database.h"
#include "headers/global_variables.h"
#include "headers/user.h"
#include "headers/product.h"

using namespace std;

int main() {
    // TODO: password should be hashed just after being passed. Proposed place of hashing is user header

    srand((unsigned)time(nullptr));

    /* ========================= USERS ========================= */
    cout << "----- USERS TESTS -----" << endl;

    /* ----- CREATING TABLE -----*/
    cout << "Creating table..." << endl;
    sqldb.createTable("USERS");
    cout << "Completed\n" << endl;
    User user;

    /* ----- REGISTERING USERS -----*/
    cout << "Register test..." << endl;
    user.registerUser("Aleksander", "Malcew");
    user.registerUser("Asia", "Neubauer");
    user.registerUser("Khar", "Thoba");
    sqldb.showTable("USERS");
    cout << "Completed\n" << endl;

    /* ----- UPDATING USERS -----*/
    cout << "Updating test..." << endl;
    sqldb.update("USERS", 1, "login", "jneubauer");
    sqldb.update("USERS", 1, "password", "qwerty");
    sqldb.showTable("USERS");
    cout << "Completed\n" << endl;

    /* ----- FINDING USERS ----- */
    cout << "Searching test..." << endl;
    if ((sqldb.find("USERS", "login", "amalcew") == 0) && (sqldb.find("USERS", "login", "jneubauer") == 1)) {
        cout << "Completed\n" << endl;
    } else {
        cout << "error!" << endl;
    }

    /* ----- DELETING USERS -----*/
    cout << "Deleting test..." << endl;
    for (int i = 0; i < userIndex; i++) sqldb.deleteRow("USERS", i);
    sqldb.showTable("USERS");
    cout << "Completed\n" << endl;

    /* ----- DROPPING TABLE -----*/
    cout << "Dropping table test..." << endl;
    sqldb.query("DROP TABLE USERS;");
    cout << "Completed\n" << endl;

    /* ========================= PRODUCTS ========================= */
    cout << "----- PRODUCTS TESTS -----" << endl;

    /* ----- CREATING TABLE ----- GIT */
    cout << "Creating table..." << endl;
    sqldb.createTable("PRODUCTS");
    cout << "Completed\n" << endl;
    Product product;

    /* ----- ADDING PRODUCTS -----*/
    cout << "Add test..." << endl;
    product.addNewProduct("Srajtasma", 5, 3.99, 84539800, "NULL", "Gospodarstwo Domowe");
    product.addNewProduct("Piwo", 12, 5.30, 33568700, "NULL", "NULL");
    product.addNewProduct("Fajki", 2, 17.89, 79359800, "Camel", "Niezbedniki");
    sqldb.showTable("PRODUCTS");
    cout << "Completed\n" << endl;
    // TODO: coś jest nie tak z przekazywaniem ceny za artykuły (dziwnie zaokrągla)

    /* ----- REMOVING PRODUCTS -----*/
    cout << "Remove test..." << endl;
    product.deleteProduct(1);
    sqldb.showTable("PRODUCTS");
    cout << "Completed\n" << endl;

    /* ----- FINDING USERS ----- */
    cout << "Searching test..." << endl;
    if ((sqldb.find("PRODUCTS", "product_name", "Fajki") == 2) && (sqldb.find("PRODUCTS", "product_name", "Srajtasma") == 0)) {
        cout << "Completed\n" << endl;
    } else {
        cout << "error!" << endl;
    }

    /* ----- UPDATING PRODUCTS -----*/
    cout << "Update test..." << endl;
    product.updateQuantity(0, 10);
    sqldb.showTable("PRODUCTS");
    cout << "Completed\n" << endl;

    /* ----- DROPPING TABLE ----- GIT */
    cout << "Dropping table test..." << endl;
    sqldb.query("DROP TABLE PRODUCTS;");
    cout << "Completed\n" << endl;

    return 0;
}