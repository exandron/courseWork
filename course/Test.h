#pragma once
#include <string>
#include "MyDate.h"
#include "AcademicUnit.h"

using namespace std;

class Test : public AcademicUnit {
private:
    bool isPassed;
public:
    Test();
    Test(string name, bool isPassed, MyDate date);
    ~Test();
    void setName(string name);
    void setIsPassed(bool isPassed);
    void setDate(MyDate date);
    string getName();
    bool getIsPassed();
    MyDate getDate();
    bool isHappened();
};