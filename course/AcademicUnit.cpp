#include "AcademicUnit.h"
#include<string>

void AcademicUnit::setName(string name) {
    this->name = name;
}

string AcademicUnit::getName() {
    return name;
}

MyDate AcademicUnit::getDate() {
    return date;
}

bool AcademicUnit::isHappened() {
    return !(date.getDay() == 1 && date.getMonth() == 1 && date.getYear() == 1);
}

void AcademicUnit::setDate(MyDate date) {
    this->date = date;
}


AcademicUnit::AcademicUnit() {
    name = "";
    date = MyDate(1, 1, 1);
}

AcademicUnit::AcademicUnit(string name, MyDate date) {
    this->name = name;
    this->date = date;
}

AcademicUnit::~AcademicUnit() {}


