#pragma once

#include <iostream>
#include <string.h>
#include <sqlite3.h>
using namespace std;

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

    void createTable() {
        // TODO: reformat the function to work on passed table/query as parameter

        /* function creating SQL table */

        sql = "CREATE TABLE USERS ("
              "ID INT PRIMARY KEY       NOT NULL,"
              "LOGIN          CHAR(50)  NOT NULL,"
              "PASSWORD       CHAR(128) NOT NULL,"
              "EMAIL          CHAR(50)"
              ")";

        // run SQL query
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    }

    void insertData(char* ID, char* login, char* password, char* email) {
        // TODO: reformat the function to work on passed table/query as parameter

        /* function which inserts the data into the table */

        char *query = nullptr;

        // build a string using asprintf (stdio.h function)
        asprintf(&query, "INSERT INTO USERS ('ID', 'LOGIN', 'PASSWORD', 'EMAIL') VALUES ('%s', '%s', '%s', '%s');", ID, login, password, email);

        // prepare the query
        sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);

        // test the query
        rc = sqlite3_step(stmt);

        // finialize the usage
        sqlite3_finalize(stmt);

        // free up the query space
        free(query);
    }

    void deleteRow(char* ID) {
        // TODO: reformat the function to work on passed table/query as parameter

        /* function which deletes given row from the table */

        char *query = nullptr;

        // build a string using asprintf (stdio.h function)
        asprintf(&query, "DELETE FROM 'USERS' WHERE ID = '%s';", ID);

        // prepare the query
        sqlite3_prepare(db, query, strlen(query), &stmt, nullptr);

        // test the query
        rc = sqlite3_step(stmt);

        // finialize the usage
        sqlite3_finalize(stmt);

        // free up the query space
        free(query);
    }

    void showTable() {
        // TODO: reformat the function to work on passed table/query as parameter

        /* function which prints the table */

        // save SQL insert data
        sql = "SELECT * FROM 'USERS';";

        // run the SQL
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    }

    void closeDB() {
        /* close the SQL connection with database */
        sqlite3_close(db);
    }
};