#include "User.h"
#include <iostream>
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    User user;
    if (user.loginIntoSystem("authorization.txt")) {
        user.menu("authorization.txt");
    }
    return 0;
}