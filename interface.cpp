#include <iostream>
#include "headers/interface.h"
#include "headers/user.h"

using std::cout;
using std::endl;

Interface::Interface() {}

void Interface::loop() {
    srand((unsigned)time(nullptr));
    User user;
    user.login();
    cout << ">";
}