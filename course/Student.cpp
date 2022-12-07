#include "Student.h"

Student::Student(int group, string name, string surname, string fathername, bool formOfEducation, bool socialLife, Exam* exams, Test* tests) {
    this->group = group;
    this->name = name;
    this->surname = surname;
    this->fathername = fathername;
    this->formOfEducation = formOfEducation;
    this->socialLife = socialLife;
    this-> tests = new Test[5];
    this->exams = new Exam[4];
    for (int i = 0; i < 5; i++) {
        this->tests[i] = tests[i];
        if (i != 4) {
            this->exams[i] = exams[i];
        }
    }
}

Student::Student() {
    tests = new Test[5];
    exams = new Exam[4];
    for (int i = 0; i < 5; i++) {
        this->tests[i] = Test("", false, MyDate(1, 1, 1));
        if (i != 4) {
            this->exams[i] = Exam("", 0, MyDate(1, 1, 1));
        }
    }
}

Student::~Student() {
    delete[] tests;
    delete[] exams;
}

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

void Student::setTests(Test* tests) {
    for (int i = 0; i < 5; i++) {
        this->tests[i] = tests[i];
    }
}

void Student::setExams(Exam* exams) {
    for (int i = 0; i < 4; i++) {
        this->exams[i] = exams[i];
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

Test* Student::getTests() {
    return tests;
}

Exam* Student::getExams() {
    return exams;
}

Student::Student(const Student& student) {
    this->group = student.group;
    this->name = student.name;
    this->surname = student.surname;
    this->fathername = student.fathername;
    this->formOfEducation = student.formOfEducation;
    this->socialLife = student.socialLife;
    this->tests = new Test[5];
    this->exams = new Exam[4];
    for (int i = 0; i < 5; i++) {
        this->tests[i] = student.tests[i];
        if (i != 4) {
            this->exams[i] = student.exams[i];
        }
    }
}

double Student::getScholarship(double scholarship) {
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
        string tokens[27];
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
                tokens[i - 6] = token;
            }
            line.erase(0, pos + delimiter.length());
        }
        Test* test = new Test[5];
        Exam* exam = new Exam[4];
        for (int i = 0; i < 27; i += 3) {
            if (i < 15) {
                test[i / 3].setName(tokens[i]);
                test[i / 3].setGrade(stoi(tokens[i + 1]));
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
                test[i / 3].setDate(newDate);
            }
            else {
                exam[(i - 15) / 3].setName(tokens[i]);
                exam[(i - 15) / 3].setGrade(stoi(tokens[i + 1]));
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
                exam[(i - 15) / 3].setDate(newDate);
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
