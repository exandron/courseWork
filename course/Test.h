#pragma once
#include <string>
#include "MyDate.h"
#include "AcademicUnit.h"

using namespace std;

class Test : public AcademicUnit<bool> {

public:
    Test();
    Test(string name, bool isPassed, MyDate date);
    ~Test();
    void setName(string name);
    void setGrade(bool isPassed);
    void setDate(MyDate date);
    string getName();
    bool getGrade();
    MyDate getDate();
    bool isHappened();
};