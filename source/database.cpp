#include <asprintf.h>
#include "headers/database.h"
#include "headers/global_variables.h"

// TODO: make sure if every function in this module is really necessary, it seems that a lot of functions is obsolete


Database::Database(char *path) {
    rc = sqlite3_open(path, &db);
    checkDBErrors();
    init();
}

Database::~Database() {
    Database::closeDB();
}

void Database::init() {
    /* performs startup checkups */

    // check if table 'USERS' exists in the database
    char *query = nullptr;
    asprintf(&query, "SELECT 1 FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'USERS'");
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    checkDBErrors();
    free(query);

    // if table 'USERS' does not exist, create it
    while ((rc = sqlite3_step(stmt)) != SQLITE_ROW) {
        cout << "\033[33m'USERS' table not found.\033[0m\nCreating table..." << endl;
        createTable("USERS");
        break;
    }

    // TODO: create for PRODUCTS
    // check if table 'PRODUCTS' exists in the database
    char *query2 = nullptr;
    asprintf(&query2, "SELECT 1 FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'PRODUCTS'");
    sqlite3_stmt *stmt2;
    rc = sqlite3_prepare_v2(db, query2, strlen(query), &stmt2, nullptr);
    checkDBErrors();
    free(query2);

    // if table 'PRODUCTS' does not exist, create it
    while ((rc = sqlite3_step(stmt2)) != SQLITE_ROW) {
        cout << "\033[33m'PRODUCTS' table not found.\033[0m\nCreating table..." << endl;
        createTable("PRODUCTS");
        break;
    }
}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName)  {
    /* sqlite3 callback */
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}

void Database::checkDBErrors() {
    /* logs database warnings and errors, used to debug */

    if (rc) {
        if (debug) {
            cout << "\033[33mDatabase Warning: " << sqlite3_errmsg(db) <<"\033[0m" << endl;
            closeDB();
        }
    }
}

void Database::createTable(char* table) {
    /* creates table with hardcoded columns */

    if (strcmp(table, "USERS")  == 0) {
        sql = "CREATE TABLE USERS ("
              "ID INTEGER PRIMARY KEY NOT NULL,"
              "LOGIN          TEXT    NOT NULL,"
              "PASSWORD       TEXT    NOT NULL,"
              "EMAIL          TEXT,"
              "IS_STAFF       BOOLEAN NOT NULL"
              ")";
    } else if (strcmp(table, "PRODUCTS")  == 0) {
        sql = "CREATE TABLE PRODUCTS ("
              "ID   INTEGER   PRIMARY KEY   NOT NULL,"
              "PRODUCT_NAME     TEXT        NOT NULL,"
              "PRIZE            REAL        NOT NULL,"
              "QUANTITY         INTEGER     NOT NULL,"
              "BARCODE          INTEGER     NOT NULL,"
              "PRODUCER_NAME    TEXT,"
              "CATEGORY         TEXT"
              ")";
    }
    rc = sqlite3_exec(db, sql, callback, nullptr, &zErrMsg);
    checkDBErrors();
}

void Database::insertData(int id, char* login, char* password, char* email, bool isStaff) {
    /* inserts user record into the table 'USERS' */

    // initialize 'query' array of chars
    char *query = nullptr;

    // copy string content with passed parameters to the char array 'query'
    asprintf(&query, "INSERT INTO USERS ('ID', 'LOGIN', 'PASSWORD', 'EMAIL', 'IS_STAFF') VALUES (%d, '%s', '%s', '%s', '%d');", id, login, password, email, isStaff);

    // convert the sql query into byte-code read by database
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);

    // evaluate the sql statement
    rc = sqlite3_step(stmt);

    // check for possible errors (logs only, if global flag 'debug' is set to true)
    checkDBErrors();

    // free memory used by 'query' array
    free(query);

    // finalize the statement if any error occurred
    sqlite3_finalize(stmt);
}

void Database::insertData(int id, char* name, float prize, long quantity, int barcode, char* producer, char* category) {
    /* inserts product record into the table 'PRODUCTS' */

    char *query = nullptr;
    if (strcmp(producer, "NULL") == 0) producer = nullptr;
    if (strcmp(category, "NULL") == 0) category = nullptr;
    asprintf(&query, "INSERT INTO PRODUCTS ('ID', 'PRODUCT_NAME', 'PRIZE', 'QUANTITY','BARCODE', 'PRODUCER_NAME', 'CATEGORY') VALUES (%d, '%s', '%f', '%ld', '%d', '%s', '%s');", id, name, prize, quantity, barcode, producer, category);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    checkDBErrors();
    free(query);
    sqlite3_finalize(stmt);
}

void Database::update(char* table, int id, char* column, long new_value) {
    /* modifies record's numeric field */

    char *query = nullptr;
    asprintf(&query, "UPDATE '%s' SET '%s' = '%ld' WHERE ID = '%d';", table, column, new_value, id);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    checkDBErrors();
    free(query);
    sqlite3_finalize(stmt);
}

void Database::update(char* table, int id, char* column, float new_value) {
    /* modifies record's numeric field */

    char *query = nullptr;
    asprintf(&query, "UPDATE '%s' SET '%s' = '%f' WHERE ID = '%d';", table, column, new_value, id);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    checkDBErrors();
    free(query);
    sqlite3_finalize(stmt);
}

void Database::update(char* table, int id, char* column, char* new_value) {
    /* modifies record's text field */

    char *query = nullptr;
    asprintf(&query, "UPDATE '%s' SET '%s' = '%s' WHERE ID = '%d';", table, column, new_value, id);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    checkDBErrors();
    free(query);
    sqlite3_finalize(stmt);
}

void Database::deleteRow(char* table, int id) {
    /* deletes record from passed table basing on passed id of the record*/

    char *query = nullptr;
    asprintf(&query, "DELETE FROM '%s' WHERE ID = '%d';", table, id);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    checkDBErrors();
    free(query);
    sqlite3_finalize(stmt);
}

int Database::find(char* table, char* columnName, char* value) {
    /* searches for record with given value in passed table and returns record's id */

    char *query = nullptr;
    int id;
    asprintf(&query, "SELECT ID FROM '%s' WHERE %s = '%s';", table, columnName, value);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    checkDBErrors();
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }
    return id;
}

bool Database::anyExists(char* table) {
    /* returns bool value if any record exist in passed table */

    char *query = nullptr;
    sqlite3_stmt *stmt;
    asprintf(&query, "SELECT * FROM '%s';", table);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    checkDBErrors();
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        return true;
    }
    return false;
}

bool Database::exists(char* table, char* columnName, int value) {
    /* returns bool value if record with passed numeric value exists in the table */

    char *query = nullptr;
    sqlite3_stmt *stmt;
    asprintf(&query, "SELECT * FROM '%s' WHERE %s = '%d';", table, columnName, value);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    checkDBErrors();
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        return true;
    }
    return false;
}

bool Database::exists(char *table, char *columnName, string value) {
    /* returns bool value if record with passed text value exists in the table */

    char* searchValue = &value[0];
    char* query = nullptr;
    sqlite3_stmt *stmt;
    asprintf(&query, "SELECT * FROM '%s' WHERE %s = '%s';", table, columnName, searchValue);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    checkDBErrors();
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        return true;
    }
    return false;
}

bool Database::authenticate(char* login, char* password) {
    /* performs user authentication, returns bool value */

    char *query = nullptr;
    sqlite3_stmt *stmt;

    asprintf(&query, "SELECT PASSWORD FROM 'USERS' WHERE login = '%s';", login);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    checkDBErrors();
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        if (strcmp(password, (char *) sqlite3_column_text(stmt, 0)) == 0) {
            return true;
        }
    }
    return false;
}

bool Database::isAdmin(char* login) {
    /* returns bool value if record with passed login has administrator permissions */

    char *query = nullptr;
    sqlite3_stmt *stmt;
    int isStaff;
    asprintf(&query, "SELECT IS_STAFF FROM 'USERS' WHERE LOGIN = '%s';", login);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    checkDBErrors();
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        isStaff = sqlite3_column_int(stmt, 0);
        if (isStaff == 1) {
            return true;
        }
    }
    return false;
}

int Database::nextId(char* table) {
    /* returns next possible id from the table, used as autoincrement method */

    if (exists(table, "ID", 0)) {
        int id;
        char *query = nullptr;
        sqlite3_stmt *stmt;
        asprintf(&query, "SELECT ID FROM '%s' WHERE ID = (SELECT MAX(ID) FROM '%s');", table, table);
        rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
        checkDBErrors();
        free(query);
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            id = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return id + 1;
        }
    }
    return 0;
}

void Database::clearDB() {
    /* drops database and creates a new one */

    char *query = nullptr;
    asprintf(&query, "DROP TABLE PRODUCTS;");
    rc = sqlite3_exec(db, query, callback, nullptr, &zErrMsg);
    checkDBErrors();
    free(query);

    sqldb.createTable("PRODUCTS");
}

void Database::closeDB() {
    /* closes database connection */

    sqlite3_close(db);
}