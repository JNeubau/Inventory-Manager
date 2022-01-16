#include "headers/admin.h"
#include "headers/global_variables.h"

void Admin::addUser(string login, string password, string email, bool isStaff) {
    char* chrLogin = &login[0];
    char* chrPassword = &password[0];
    char* chrEmail = &email[0];
    sqldb.insertData(sqldb.nextId("USERS"), chrLogin, chrPassword, chrEmail, isStaff);
}

void Admin::deleteUser(string login) {
    char* chrLogin = &login[0];
    int index = sqldb.find("USERS", "LOGIN", chrLogin);
    if (strcmp(chrLogin, (char *) selfLogin) != 0) {
        sqldb.deleteRow("USERS", index);
    } else {
        cout << "\033[1;31mCannot delete active account\033[0m" << endl;
    }
}

void Admin::modifyUser(string login, string field, string newValue) {
    char* chrLogin = &login[0];
    char* chrField = &field[0];
    char* chrNewValue = &newValue[0];
    int index = sqldb.find("USERS", "LOGIN", chrLogin);
    sqldb.update("USERS", index, chrField, chrNewValue);
}

void Admin::modifyUser(string login, string field, int newValue) {
    char* chrLogin = &login[0];
    char* chrField = &field[0];
    int index = sqldb.find("USERS", "LOGIN", chrLogin);
    sqldb.update("USERS", index, chrField, newValue);
}

void Admin::dropDatabase(char *table) {
    sqldb.dropDB(table);
}