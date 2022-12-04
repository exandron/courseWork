#include "Test.h"

Test::Test() {
    name = "";
    isPassed = false;
    date = MyDate(1, 1, 1);
}

Test::Test(string name, bool isPassed, MyDate date) {
    this->name = name;
    this->isPassed = isPassed;
    this->date = date;
}

Test::~Test() {}


void Test::setIsPassed(bool isPassed) {
    this->isPassed = isPassed;
}


bool Test::getIsPassed() {
    return isPassed;
}

