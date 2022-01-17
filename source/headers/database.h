#pragma once

#include "../../sqlite3/sqlite3.h"   // use on Windows 10
//#include <sqlite3.h>  // use on Linux
#include <iostream>
#include <cstring>
#include <string>

using std::cout;
using std::string;
using std::endl;

class Database {
private:
    sqlite3 *db{};         // pointer to SQLite connection
    char *zErrMsg{};       // Save any error messages
    int rc;                // result of opening the file
    char *sql{};           // SQL query
    sqlite3_stmt *stmt{};  // compiled SQLite statement

    void init();

    static int callback(void* NotUsed, int argc, char** argv, char** azColName);

    void checkDBErrors();

protected:
    void createTable(char* table);

public:
    explicit Database(char* path);

    ~Database();

    void insertData(int id, char* login, char* password, char* email, bool isStaff);

    void insertData(int id, char* name, float prize, long quantity, int barcode, char* producer, char* category);

    void update(char* table, int id, char* column, long new_value);

    void update(char* table, int id, char* column, char* new_value);

    void deleteRow(char* table, int id);

    int find(char* table, char* columnName, char* value);

    bool anyExists(char* table);

    bool exists(char* table, char* columnName, int value);

    bool exists(char* table, char* columnName, string value);

    bool authenticate(char* login, char* password);

    bool isAdmin(char* login);

    int nextId(char* table);

    void closeDB();
};