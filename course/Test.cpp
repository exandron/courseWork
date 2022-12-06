#include "Test.h"

Test::Test() {
    name = "";
    grade = false;
    date = MyDate(1, 1, 1);
}

Test::Test(string name, bool isPassed, MyDate date) {
    this->name = name;
    this->grade = isPassed;
    this->date = date;
}

Test::~Test() {}


void Test::setGrade(bool isPassed) {
    this->grade = isPassed;
}


bool Test::getGrade() {
    return grade;
}

void Test::setName(string name) {
    this->name = name;
}

string Test::getName() {
    return name;
}

MyDate Test::getDate() {
    return date;
}

bool Test::isHappened() {
    return !(date.getDay() == 1 && date.getMonth() == 1 && date.getYear() == 1);
}

void Test::setDate(MyDate date) {
    this->date = date;
}
