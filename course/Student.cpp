#include "Student.h"

Student::Student(int group, string name, string surname, string fathername, bool formOfEducation, bool socialLife, vector<Exam> exams, vector<Test> tests) {
    this->group = group;
    this->name = name;
    this->surname = surname;
    this->fathername = fathername;
    this->formOfEducation = formOfEducation;
    this->socialLife = socialLife;
    for (int i = 0; i < 5; i++) {
        this->tests.push_back(tests[i]);
        if (i != 4) {
            this->exams.push_back(exams[i]);
        }
    }
}

Student::Student() {}

void Student::setGroup(int group) {
    this->group = group;
}

void Student::setName(string name) {
    this->name = name;
}

void Student::setSurname(string surname) {
    this->surname = surname;
}

void Student::setFathername(string fathername) {
    this->fathername = fathername;
}

void Student::setFormOfEducation(bool formOfEducation) {
    this->formOfEducation = formOfEducation;
}

void Student::setSocialLife(bool socialLife) {
    this->socialLife = socialLife;
}

void Student::setTests(vector<Test> tests) {
    this->tests.clear();
    for (int i = 0; i < 5; i++) {
        this->tests.push_back(tests[i]);
    }
}

void Student::setExams(vector<Exam> exams) {
    this->exams.clear();
    for (int i = 0; i < 4; i++) {
        this->exams.push_back(exams[i]);
    }
}

int Student::getGroup() {
    return group;
}

string Student::getName() {
    return name;
}

string Student::getSurname() {
    return surname;
}

string Student::getFathername() {
    return fathername;
}

bool Student::getFormOfEducation() {
    return formOfEducation;
}

bool Student::getSocialLife() {
    return socialLife;
}

vector<Test> Student::getTests() {
    return tests;
}

vector<Exam> Student::getExams() {
    return exams;
}

Student::Student(const Student& student) {
    this->group = student.group;
    this->name = student.name;
    this->surname = student.surname;
    this->fathername = student.fathername;
    this->formOfEducation = student.formOfEducation;
    this->socialLife = student.socialLife;
    for (int i = 0; i < 5; i++) {
        this->tests.push_back(student.tests[i]);
        if (i != 4) {
            this->exams.push_back(student.exams[i]);
        }
    }
}

void Student::printFullName() {
    cout << surname << " " << name << " " << fathername;
}

double Student::getMiddleGrade() {
    double middleGrade = 0;
    double count = 0;
    for (int i = 0; i < 4; i++) {
        if (exams[i].getGrade() > 0) {
            middleGrade += exams[i].getGrade();
            count++;
        }
    }

    return middleGrade / count;
}

istream& operator>>(istream& in, Student& student) {
    if (in.peek() != EOF) {
        string line;
        getline(in, line);
        size_t pos = 0;
        string delimiter = ";";
        vector<string> tokens;
        for (int i = 0; (pos = line.find(delimiter)) != string::npos; i++) {
            string token = line.substr(0, pos);
            switch (i) {
            case 0:
                student.setGroup(stoi(token));
                break;
            case 1:
                student.setSurname(token);
                break;
            case 2:
                student.setName(token);
                break;
            case 3:
                student.setFathername(token);
                break;
            case 4:
                student.setFormOfEducation(stoi(token) != 0);
                break;
            case 5:
                student.setSocialLife(stoi(token) != 0);
                break;
            default:
                tokens.push_back(token);
            }
            line.erase(0, pos + delimiter.length());
        }
        vector<Test> test;
        vector<Exam> exam;
        for (int i = 0; i < 27; i += 3) {
            if (i < 15) {
                Test tmpTest;
                tmpTest.setName(tokens[i]);
                tmpTest.setGrade(stoi(tokens[i + 1]));
                pos = 0;
                delimiter = "/";
                MyDate newDate;
                tokens[i + 2] += delimiter;
                for (int j = 0; (pos = tokens[i + 2].find(delimiter)) != string::npos; j++) {
                    string token = tokens[i + 2].substr(0, pos);
                    switch (j) {
                    case 0:
                        newDate.setDay(stoi(token));
                        break;
                    case 1:
                        newDate.setMonth(stoi(token));
                        break;
                    case 2:
                        newDate.setYear(stoi(token));
                        break;
                    }
                    tokens[i + 2].erase(0, pos + delimiter.length());
                }
                tmpTest.setDate(newDate);
                test.push_back(tmpTest);
            }
            else {
                Exam tmpExam;
                tmpExam.setName(tokens[i]);
                tmpExam.setGrade(stoi(tokens[i + 1]));
                pos = 0;
                delimiter = "/";
                MyDate newDate;
                tokens[i + 2] += delimiter;
                for (int j = 0; (pos = tokens[i + 2].find(delimiter)) != string::npos; j++) {
                    string token = tokens[i + 2].substr(0, pos);
                    switch (j) {
                    case 0:
                        newDate.setDay(stoi(token));
                        break;
                    case 1:
                        newDate.setMonth(stoi(token));
                        break;
                    case 2:
                        newDate.setYear(stoi(token));
                        break;
                    }
                    tokens[i + 2].erase(0, pos + delimiter.length());
                }
                tmpExam.setDate(newDate);
                exam.push_back(tmpExam);
            }
        }
        student.setTests(test);
        student.setExams(exam);
    }
    return in;
}

ostream& operator<<(ostream& out, Student& student) {
    out << student.getGroup() << ";" << student.getSurname() << ";" << student.getName() << ";" << student.getFathername() << ";" << student.getFormOfEducation() << ";" << student.getSocialLife() << ";";
    for (int i = 0; i < 9; i++) {
        if (i < 5) {
            out << student.getTests()[i].getName() << ";" << student.getTests()[i].getGrade() << ";" << student.getTests()[i].getDate().getDay() << "/" << student.getTests()[i].getDate().getMonth() << "/" << student.getTests()[i].getDate().getYear() << ";";
        }
        else {
            out << student.getExams()[i - 5].getName() << ";" << student.getExams()[i - 5].getGrade() << ";" << student.getExams()[i - 5].getDate().getDay() << "/" << student.getExams()[i - 5].getDate().getMonth() << "/" << student.getExams()[i - 5].getDate().getYear() << ";";

        }
    }
    return out;
}