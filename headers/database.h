#pragma once

#include "asprintf.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "../sqlite3/sqlite3.h"  // use on Windows 10
/* #include <sqlite3.h> */ // use on Linux

using std::cout;
using std::endl;

class Database {
private:
    sqlite3 *db{};         // pointer to SQLite connection
    char *zErrMsg{};       // Save any error messages
    int rc;                // result of opening the file
    char *sql{};           // SQL query
    sqlite3_stmt *stmt{};  // compiled SQLite statement

    static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        for (int i = 0; i < argc; i++) {
            cout << azColName[i] << ": " << argv[i] << endl;
        }
        cout << endl;
        return 0;
    }

    void checkDBErrors() {
        /* function used in Database() constructor, to check for potential errors*/

        if (rc) {
            // show an error message
            cout << "Database Error: " << sqlite3_errmsg(db) << endl;
            closeDB();
        }
    }

public:
    explicit Database(char* path) {
        /* CONSTRUCTOR */

        // open database with given path
        rc = sqlite3_open(path, &db);
        checkDBErrors();
    }
    ~Database() {
        /* DESTRUCTOR */

        // close the SQL connection
        sqlite3_close(db);
    }

    void createTable(char* table) {
        /* function creating SQL table */

        if (strcmp(table, "USERS")  == 0) {
            sql = "CREATE TABLE USERS ("
                  "ID INTEGER PRIMARY KEY NOT NULL,"
                  "LOGIN          TEXT    NOT NULL,"
                  "PASSWORD       TEXT    NOT NULL,"
                  "EMAIL          TEXT"
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
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        // checkDBErrors();
    }

    void insertData(int id, char* login, char* password, char* email) {
        // TODO: override the function and allow it to work both for User objects and Product objects
        // TODO: można tu spróbować z przeciążeniem zrobić? Tak mi się coś kojarzy że tam było coś pomocnego to tego

        /* function which inserts the data into the table */

        char *query = nullptr;

        // build a string using asprintf (stdio.h function)
        asprintf(&query, "INSERT INTO USERS ('ID', 'LOGIN', 'PASSWORD', 'EMAIL') VALUES (%d, '%s', '%s', '%s');", id, login, password, email);

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

    void insertDataForProducts(int id, char* name, float prize, long quantity, int barcode, char* producer, char* category) {
        /* function which inserts the data into the table */
        char *query = nullptr;

        if (strcmp(producer, "NULL") == 0) producer = nullptr;
        if (strcmp(category, "NULL") == 0) category = nullptr;

        // build a string using asprintf (stdio.h function)
        asprintf(&query, "INSERT INTO PRODUCTS ('ID', 'PRODUCT_NAME', 'PRIZE', 'QUANTITY',"
                         " 'BARCODE', 'PRODUCER_NAME', 'CATEGORY') VALUES (%d, '%s', '%f', '%ld', '%d', '%s', '%s');", id, name, prize, quantity, barcode, producer, category);

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

    void deleteRow(int id, char* table) {
        /* function which deletes given row from the table */

        char *query = nullptr;
        asprintf(&query, "DELETE FROM '%s' WHERE ID = '%d';", table, id);
        sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
        rc = sqlite3_step(stmt);
        // checkDBErrors();
        sqlite3_finalize(stmt);
        free(query);
    }

    // TODO: new_value must accept other data types
    void updateInfo(int id, char* column, long new_value, char* table) {
        char *query = nullptr;
        asprintf(&query, "UPDATE '%s' SET '%s' = '%ld' WHERE ID = '%d';", table, column, new_value, id);
        sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);
        rc = sqlite3_step(stmt);
        // checkDBErrors();
        sqlite3_finalize(stmt);
        free(query);
    }
    /* UPDATE table_name
    SET column1 = value1, column2 = value2...., columnN = valueN
    WHERE [condition]; */

    void showTable(char* table) {
        /* function which prints the table */

        char *query = nullptr;
        asprintf(&query, "SELECT * FROM '%s';", table);
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
        cout << "-------------------" << endl;
        // checkDBErrors();
        free(query);
    }

    void query(char* content) {
        /* more universal function to pass query to the database, created specifically to debug */

        char *query = nullptr;
        asprintf(&query, "%s", content);
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
        // checkDBErrors();
        free(query);
    }

    // TODO: create a function that searches for the right ID
//    int findID(char* table, char* columnName, char* value) {
//        char *query = nullptr;
//        asprintf(&query, "SELECT ID FROM '%s' WHERE '%s' = '%s';", table, columnName, value);
//        rc = sqlite3_exec(db, query, callback, nullptr, &zErrMsg);
//        return (int)rc;
//    }

    void closeDB() {
        /* close the SQL connection with database */

        sqlite3_close(db);
    }
};