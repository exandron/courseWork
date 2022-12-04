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

