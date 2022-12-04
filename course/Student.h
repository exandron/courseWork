#pragma once
#include <string>
#include <iostream>
#include "Exam.h"
#include "Test.h"
#include <vector>

using namespace std;

class Student {
private:
    int group;
    string name;
    string surname;
    string fathername;
    bool formOfEducation;
    bool socialLife;
    vector<Exam> exams;
    vector<Test> tests;
public:
    Student();
    Student(int group, string name, string surname, string fathername, bool formOfEducation, bool socialLife, vector<Exam> exams, vector<Test> tests);
    Student(const Student& student);
    void setGroup(int group);
    void setName(string name);
    void setSurname(string surname);
    void setFathername(string fathername);
    void setFormOfEducation(bool formOfEducation);
    void setSocialLife(bool socialLife);
    void setTests(vector<Test> tests);
    void setExams(vector<Exam> exams);
    int getGroup();
    string getName();
    string getSurname();
    string getFathername();
    bool getFormOfEducation();
    bool getSocialLife();
    vector<Test> getTests();
    vector<Exam> getExams();
    double getScholarship(double scholarship);
    void printFullName();
    double getMiddleGrade();
    friend istream& operator >> (istream& in, Student& student);
    friend ostream& operator << (ostream& out, Student& student);
};
