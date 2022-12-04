#include "User.h"
#include <iostream>
#include <Windows.h>

int main() {
    User user;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    if (user.loginIntoSystem("authorization.txt")) {
        user.menu("authorization.txt");
    }
    return 0;
}
