#include "headers/database.h"
#include "headers/asprintf.h"
#include "headers/global_variables.h"

// TODO:
//  1) make sure if every function in this module is really necessary, it seems that a lot of functions is obsolete
//  2) properly comment the functions


Database::Database(char *path) {
    /* CONSTRUCTOR */

    // open database with given path
    rc = sqlite3_open(path, &db);
    init();
    checkDBErrors();
}

Database::~Database() {
    /* DECONSTRUCTOR */

    // close the database connection
    Database::closeDB();
}

void Database::init() {
    /* initialization function */

    char *query = nullptr;
    asprintf(&query, "select 1 from sqlite_master where type='table' and name='USERS'");

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    free(query);
    while ((rc = sqlite3_step(stmt)) != SQLITE_ROW) {
        cout << "'USERS' table not found.\nCreating table..." << endl;
        createTable("USERS");
        break;
    }

}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName)  {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}

void Database::checkDBErrors() {
    /* function used in Database() constructor, to check for potential errors*/

    if (rc) {
        // show an error message
        cout << "Database Error: " << sqlite3_errmsg(db) << endl;
        closeDB();
    }
}

void Database::createTable(char* table) {
    /* function creating SQL table */

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
    } else {
        cout << "Database Error: wrong table passed" << endl;
        return;
    }

    // run SQL query
    rc = sqlite3_exec(db, sql, callback, nullptr, &zErrMsg);
    // checkDBErrors();
}

void Database::insertData(int id, char* login, char* password, char* email, bool isStaff) {
    /* function which inserts the data into the USERS table */

    char *query = nullptr;

    // build a string using asprintf (stdio.h function)
    asprintf(&query, "INSERT INTO USERS ('ID', 'LOGIN', 'PASSWORD', 'EMAIL', 'IS_STAFF') VALUES (%d, '%s', '%s', '%s', '%d');", id, login, password, email, isStaff);

    // prepare the query
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);

    // test the query
    rc = sqlite3_step(stmt);
    // checkDBErrors();

    // finalize the usage
    sqlite3_finalize(stmt);

    // free up the query space
    free(query);
}

void Database::insertData(int id, char* name, float prize, long quantity, int barcode, char* producer, char* category) {
    /* function which inserts the data into the PRODUCTS table */

    char *query = nullptr;

    if (strcmp(producer, "NULL") == 0) producer = nullptr;
    if (strcmp(category, "NULL") == 0) category = nullptr;

    // build a string using asprintf (stdio.h function)
    asprintf(&query, "INSERT INTO PRODUCTS ('ID', 'PRODUCT_NAME', 'PRIZE', 'QUANTITY','BARCODE', 'PRODUCER_NAME', 'CATEGORY') VALUES (%d, '%s', '%f', '%ld', '%d', '%s', '%s');", id, name, prize, quantity, barcode, producer, category);

    // prepare the query
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);

    // test the query
    rc = sqlite3_step(stmt);
    // checkDBErrors();

    // finalize the usage
    sqlite3_finalize(stmt);

    // free up the query space
    free(query);
}

void Database::update(char* table, int id, char* column, long new_value) {
    /* function which updates given numeric value from the table */

    char *query = nullptr;
    asprintf(&query, "UPDATE '%s' SET '%s' = '%ld' WHERE ID = '%d';", table, column, new_value, id);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    // checkDBErrors();
    sqlite3_finalize(stmt);
    free(query);
}

void Database::update(char* table, int id, char* column, char* new_value) {
    /* function which updates given string value from the table */

    char *query = nullptr;
    asprintf(&query, "UPDATE '%s' SET '%s' = '%s' WHERE ID = '%d';", table, column, new_value, id);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    // checkDBErrors();
    sqlite3_finalize(stmt);
    free(query);
}

void Database::deleteRow(char* table, int id) {
    /* function which deletes given row from the table */

    char *query = nullptr;
    asprintf(&query, "DELETE FROM '%s' WHERE ID = '%d';", table, id);
    sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
    rc = sqlite3_step(stmt);
    // checkDBErrors();
    sqlite3_finalize(stmt);
    free(query);
}

bool Database::exists(char* table, char* columnName, int value) {
    /* function returning bool value, if row exists in passed table  */

    char *query = nullptr;
    sqlite3_stmt *stmt;

    asprintf(&query, "SELECT * FROM '%s' WHERE %s = '%d';", table, columnName, value);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);

    // if rc points to a row, continue the query
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        return true;
    }
    return false;
}

bool Database::login(char* login, char* password) {
    /* database method returning boolean variable if given login credentials appear in the database */

    char *query = nullptr;
    sqlite3_stmt *stmt;

    asprintf(&query, "SELECT PASSWORD FROM 'USERS' WHERE login = '%s';", login);
    rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);
    free(query);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        if (strcmp(password, (char *) sqlite3_column_text(stmt, 0)) == 0) {
            return true;
        }
    }
    return false;
}

int Database::nextId(char* table) {
    /* returns next id available in passed table */

    if (exists(table, "ID", 0)) {
        int id;
        char *query = nullptr;
        sqlite3_stmt *stmt;

        asprintf(&query, "SELECT ID FROM '%s' WHERE ID = (SELECT MAX(ID) FROM '%s');", table, table);
        rc = sqlite3_prepare_v2(db, query, strlen(query), &stmt, nullptr);

        // if rc points to a row, continue the query
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            id = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            free(query);
            return id + 1;
        }
    } else {
        return 0;
    }
}


void Database::closeDB() {
    /* close the SQL connection with database */

    sqlite3_close(db);
}

void Database::dropDB(char* table) {
    /* drop given database passed as parameter */

    char *query = nullptr;
    asprintf(&query, "DROP TABLE %s", table);
    rc = sqlite3_exec(db, query, callback, nullptr, &zErrMsg);
    // checkDBErrors();
    free(query);
}

void Database::showTable(char* table) {
    /* function which prints the table */

    char *query = nullptr;
    asprintf(&query, "SELECT * FROM '%s';", table);
    rc = sqlite3_exec(db, query, callback, nullptr, &zErrMsg);
    cout << "<- EOF ->" << endl;
    // checkDBErrors();
    free(query);
}

void Database::query(char* content) {
    /* more universal function to pass query to the database, created specifically to debug */

    char *query = nullptr;
    asprintf(&query, "%s", content);
    rc = sqlite3_exec(db, query, callback, nullptr, &zErrMsg);
    // checkDBErrors();
    free(query);
}