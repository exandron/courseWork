#pragma once
#include<fstream>
#include <string>
#include <iostream>
#include <string>
#include "Student.h"
#include "User.h"
#include <vector>

using namespace std;

class Students {
private:
    vector<Student> students;
    Student inputStudentInformation();
    void sortStudentsByOption(int option, int sort);
public:
    Students();
    ~Students();
    static int getSizeFromFile(string filename);
    void readStudentsFromFile(string filename);
    void writeStudentsIntoFile(string filename);
    void addStudent();
    void editStudent();
    void deleteStudent();
    void searchStudent();
    void getScholarshipStat();
    void sortStudents();
    void filterStudents();
    void printInfo();
    void setStudents(vector<Student> students) {
        this->students = students;
    };
    vector<Student> getStudents() {
        return students;
    };
    bool isSymbolic(int valToCheck)
    {
        bool returnVar = false;
        if (!cin) {
            cout << "Вводите только цифры!" << endl;
            cin.clear();
            while (cin.get() != '\n');
            returnVar = true;
        }
        return returnVar;
    }
    int getSize() {
        return students.size();
    }
    void printStudents(vector<Student> students, int size);
    void printSortedStudents(vector<Student> students, int size);
    bool isDate(string date) {
        size_t pos = 0;
        string delimiter = "/";
        date += delimiter;
        int j = 0;
        for (; (pos = date.find(delimiter)) != string::npos; j++) {
            string token = date.substr(0, pos);
            if (!isNumeric(token))
                return false;
            switch (j) {
            case 0:
                if ((stoi(token) <= 0 || stoi(token) > 31) && !isSymbolic(stoi(token)))
                    return false;
                break;
            case 1:
                if ((stoi(token) <= 0 || stoi(token) > 12) && !isSymbolic(stoi(token)))
                    return false;
                break;
            case 2:
                if ((stoi(token) <= 0) && !isSymbolic(stoi(token)))
                    return false;
                break;
            default: return false;
            }
            date.erase(0, pos + delimiter.length());
        }
        if (j != 3) { return false; }
        return true;
    };
    bool isNumeric(string line) {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] < '0' || line[i]>'9')
                return false;
        }
        return true;
    }
}; 
