#include "headers/admin.h"
#include "headers/global_variables.h"

void Admin::addUser(string login, string password, string email, bool isStaff) {
    /* performs a query adding user into the database */

    sqldb.insertData(sqldb.nextId("USERS"), &login[0], &password[0], &email[0], isStaff);
}

void Admin::deleteUser(string login) {
    /* performs a query deleting user from the database */

    int index = sqldb.find("USERS", "LOGIN", &login[0]);

    // allow to delete an user only, if it isn't an active user
    if (strcmp(&login[0], (char *) selfLogin) != 0) {
        sqldb.deleteRow("USERS", index);
    } else {
        cout << "\033[1;31mCannot delete active account\033[0m" << endl;
    }
}

void Admin::modifyUser(string login, string field, string newValue) {
    /* performs a query modifying an existing user's text field */

    int index = sqldb.find("USERS", "LOGIN", &login[0]);
    sqldb.update("USERS", index, &field[0], &newValue[0]);
}

void Admin::modifyUser(string login, string field, int newValue) {
    /* performs a query modifying an existing user's numeric field */

    int index = sqldb.find("USERS", "LOGIN", &login[0]);
    sqldb.update("USERS", index, &field[0], (long)newValue);
    // TODO: To nie jest todo -> zmieniłam newValue na (long)newValue bo się nie kompilowało, nwm czy ci to odpowiada? Feel free do zmian
}