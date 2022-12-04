#include "Exam.h"

Exam::Exam() {
    name = "";
    grade = 0;
    date = MyDate(1, 1, 1);
}

Exam::Exam(string name, int grade, MyDate date) {
    this->name = name;
    this->grade = grade;
    this->date = date;
}

Exam::~Exam() {}

void Exam::setGrade(int grade) {
    this->grade = grade;
}

int Exam::getGrade() {
    return grade;
}
void Exam::setName(string name) {
    this->name = name;
}

string Exam::getName() {
    return name;
}

MyDate Exam::getDate() {
    return date;
}

bool Exam::isHappened() {
    return !(date.getDay() == 1 && date.getMonth() == 1 && date.getYear() == 1);
}

void Exam::setDate(MyDate date) {
    this->date = date;
}


