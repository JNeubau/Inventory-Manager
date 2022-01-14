#pragma once

/* #include "../sqlite3/sqlite3.h" */  // use on Windows 10
#include <sqlite3.h>  // use on Linux
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using std::cout;
using std::endl;

class Database {
private:
    sqlite3 *db{};         // pointer to SQLite connection
    char *zErrMsg{};       // Save any error messages
    int rc;                // result of opening the file
    char *sql{};           // SQL query
    sqlite3_stmt *stmt{};  // compiled SQLite statement
    // int data;           // stores id for competing a select query

    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

    void checkDBErrors();

    bool checkAdmin();

public:
    explicit Database(char* path);

    ~Database();

    void createTable(char* table);

    void insertData(int id, char* login, char* password, char* email);

    void insertData(int id, char* name, float prize, long quantity, int barcode, char* producer, char* category);

    void update(char* table, int id, char* column, long new_value);

    void update(char* table, int id, char* column, char* new_value);

    void deleteRow(char* table, int id);

    int find(char* table, char* columnName, char* value);

    bool login(char* login, char* password);

    void closeDB();

    void dropDB(char* table);

    void showTable(char* table);

    void query(char* content);
};