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

void Exam::setName(string name) {
    this->name = name;
}

void Exam::setGrade(int grade) {
    this->grade = grade;
}

void Exam::setDate(MyDate date) {
    this->date = date;
}

string Exam::getName() {
    return name;
}

int Exam::getGrade() {
    return grade;
}

MyDate Exam::getDate() {
    return date;
}

bool Exam::isHappened() {
    return !(date.getDay() == 1 && date.getMonth() == 1 && date.getYear() == 1);
}
