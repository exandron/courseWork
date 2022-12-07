#pragma once
#include <string>
#include <iostream>
#include "Exam.h"
#include "Test.h"

using namespace std;

class Student {
private:
    int group;
    string name;
    string surname;
    string fathername;
    bool formOfEducation;
    bool socialLife;
    Exam* exams;
    Test* tests;

public:
    Student();
    Student(int group, string name, string surname, string fathername, bool formOfEducation, bool socialLife, Exam* exam, Test* tests);
    Student(const Student& student);
    ~Student();
    void setGroup(int group);
    void setName(string name);
    void setSurname(string surname);
    void setFathername(string fathername);
    void setFormOfEducation(bool formOfEducation);
    void setSocialLife(bool socialLife);
    void setTests(Test* tests);
    void setExams(Exam* exams);
    int getGroup();
    string getName();
    string getSurname();
    string getFathername();
    bool getFormOfEducation();
    bool getSocialLife();
    Test* getTests();
    Exam* getExams();
    double getScholarship(double scholarship);
    void printFullName();
    double getMiddleGrade();
    friend istream& operator >> (istream& in, Student& student);
    friend ostream& operator << (ostream& out, Student& student);
};


