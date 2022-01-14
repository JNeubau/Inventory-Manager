#include "headers/user.h"
#include "headers/global_variables.h"

void Admin::addUser(char *login, char *password, char *email, bool isStaff) {
    sqldb.insertData(userIndex++, login, password, email, isStaff);
}

void Admin::blockUser() {}

void Admin::deleteUser(int index) {
    sqldb.deleteRow("USERS", index);
}

void Admin::deleteUser(char *login) {
    int index = sqldb.find("USERS", "login", login);
    sqldb.deleteRow("USERS", index);
}

void Admin::modifyUser(char *login, char *field, char *new_value) {
    int index = sqldb.find("USERS", "login", login);
    sqldb.update("USERS", index, field, new_value);
}

void Admin::dropDatabase(char *table) {
    sqldb.dropDB(table);
}