#include "headers/database.h"
using namespace std;

int main() {
    // TODO:
    //  1) implement passing the arguments into the table as variables of object User
    //  2) password should be hashed just after being passed. Proposed place of hashing is user header

    Database sqldb("../database/sqlite3.db");  // change if needed
    sqldb.createTable();
    sqldb.insertData("1", "amalcew", "q1w2e3r4", "amalcew@protonmail.com");
    sqldb.insertData("2", "jneubauer", "abcdefgh", "");
    sqldb.insertData("3", "psobczak", "qwerty", "psobczak@gardens.com");
    sqldb.showTable();
    sqldb.deleteRow("2");
    sqldb.showTable();
    return 0;
}