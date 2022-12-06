#pragma once
#include<string>
#include"MyDate.h"

using namespace std;

template <class T>
class AcademicUnit {
protected:
    string name;
    MyDate date;
    T grade;
public:
    AcademicUnit() {
        name = "";
        date = MyDate(1, 1, 1);
        grade = 0;
    };
    AcademicUnit(string name, MyDate date, T grade) {
        this->name = name;
        this->date = date;
        this->grade = grade;
    };
    ~AcademicUnit() {};
    virtual void setName(string name) = 0;
    virtual void setDate(MyDate date) = 0;
    virtual string getName() = 0;
    virtual MyDate getDate() = 0;
    virtual bool isHappened() = 0;
    virtual void setGrade(T grade) = 0;
    virtual T getGrade() = 0;
};