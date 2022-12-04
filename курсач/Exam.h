#pragma once
#include <string>
#include "MyDate.h"

using namespace std;

class Exam {
private:
    string name;
    int grade;
    MyDate date;

public:
    Exam();
    Exam(string name, int grade, MyDate date);
    ~Exam();
    void setName(string name);
    void setGrade(int grade);
    void setDate(MyDate date);
    string getName();
    int getGrade();
    MyDate getDate();
    bool isHappened();
};
