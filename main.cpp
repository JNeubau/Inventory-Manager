#include "headers/database.h"
#include "headers/init.h"
#include "headers/user.h"

using namespace std;

int main() {
    // TODO: password should be hashed just after being passed. Proposed place of hashing is user header

    sqldb.createTable();
    User user;
    user.registerUser("amalcew", "qwerty", "amalcew@protonmail.com");
    user.registerUser("fenix12", "hjklaDfeaw", "jneubauer@gmail.com");
    sqldb.showTable("USERS");
    return 0;
}