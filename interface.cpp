#include "headers/interface.h"
#include "headers/user.h"
#include "headers/global_variables.h"
#include "headers/database.h"

using std::cout;
using std::endl;

void Interface::run() {
    if (sqldb.exists("USERS", "ID", 0)) {
        cout << "Select action:\n\t[l] login\n\t[r] register\n\t[x] exit" << endl;
        while (true) {
            cout << "> ";
            string flag;
            cin >> flag;
            if (flag[0] == 'l' || flag[0] == 'L'){
                globalUser.login();
                break;
            } else if (flag[0] == 'r' || flag[0] == 'R') {
                User newUser;
                newUser.registerUser(false);
                globalUser.login();
                break;
            } else if (flag[0] == 'x' || flag[0] == 'X') {
                exit(1);
            } else {
                cout << "Unknown mode, please try again" << endl;
                continue;
            }
        }
    } else {
        cout << "Select action:\n\t[r] register\n\t[x] exit" << endl;
        while (true) {
            cout << "> ";
            string flag;
            cin >> flag;
            if (flag[0] == 'r' || flag[0] == 'R') {
                User newUser;
                newUser.registerUser(false);
                globalUser.login();
                break;
            } else if (flag[0] == 'x' || flag[0] == 'X') {
                exit(1);
            } else {
                cout << "Unknown mode, please try again" << endl;
                continue;
            }
        }
    }
}