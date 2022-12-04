#pragma once
#include<string>
#include"MyDate.h"

using namespace std;

class AcademicUnit {
protected:
    string name;
    MyDate date;
public:
    AcademicUnit();
    AcademicUnit(string name, MyDate date);
    ~AcademicUnit();
    virtual void setName(string name) = 0;
    virtual void setDate(MyDate date) = 0;
    virtual string getName() = 0;
    virtual MyDate getDate() = 0;
    virtual bool isHappened() = 0;
};