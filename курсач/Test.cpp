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

void Test::setName(string name) {
    this->name = name;
}

void Test::setIsPassed(bool isPassed) {
    this->isPassed = isPassed;
}

void Test::setDate(MyDate date) {
    this->date = date;
}

string Test::getName() {
    return name;
}

bool Test::getIsPassed() {
    return isPassed;
}

MyDate Test::getDate() {
    return date;
}

bool Test::isHappened() {
   return !(date.getDay() == 1 && date.getMonth() == 1 && date.getYear() == 1);
}
