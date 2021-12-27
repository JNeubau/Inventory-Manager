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
        } else if (strcmp(table, "PRODUCTS")  == 0){
            /*
             products query goes here
            */
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

    void closeDB() {
        /* close the SQL connection with database */

        sqlite3_close(db);
    }
};