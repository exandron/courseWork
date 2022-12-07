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
    template <class T>
    T getScholarship(T scholarship) {
        if (formOfEducation == 0) {
            return 0;
        }
        else {
            for (int i = 0; i < 5; i++) {
                if (tests[i].isHappened() && !tests[i].getGrade()) {
                    return 0;
                }
                if (!tests[i].isHappened()) {
                    return  -1;
                }
            }
            for (int i = 0; i < 4; i++) {
                if (exams[i].getGrade() < 4 && exams[i].isHappened()) {
                    return 0;
                }
                if (!exams[i].isHappened()) {
                    return -1;
                }
            }
            bool excellent = true;
            double middleGrade = 0;
            for (int i = 0; i < 4; i++) {
                middleGrade += exams[i].getGrade();
                if (exams[i].getGrade() < 9) {
                    excellent = false;
                }
            }
            if (excellent && socialLife == 1) {
                return scholarship * 1.5;
            }
            else if (excellent && socialLife == 0) {
                return scholarship * 1.25;
            }
            else if (middleGrade / 4 > 5) {
                return scholarship;
            }
            else {
                return 0;
            }
        }
    };
    void printFullName();
    double getMiddleGrade();
    friend istream& operator >> (istream& in, Student& student);
    friend ostream& operator << (ostream& out, Student& student);
};


