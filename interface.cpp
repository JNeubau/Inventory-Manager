#include "headers/interface.h"
#include "headers/user.h"
#include "headers/global_variables.h"

using std::cout;
using std::endl;

void Interface::loop() {
    srand((unsigned)time(nullptr));
    User user;
    user.login();
    cout << ">";
}