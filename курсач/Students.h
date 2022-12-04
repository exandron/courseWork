#include<fstream>
#include <string>
#include <iostream>
#include <string>
#include "Student.h"
#include"User.h"

using namespace std;

class Students : public Student {
private:
    Student* students;
    int size;
    Student inputStudentInformation();
    void sortStudentsByOption(int option, int sort);
public:
    Students();
    Students(int size);
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
    void printInfo();
    void setStudents(Student* students) {
        this->students = students;
    };
    void setSize(int size) {
        this->size = size;
    };
    Student* getStudents() {
       return students;
    };
    int getSize() {
        return size;
    }
    bool isSymbolic(int valToCheck) // Проверка на символ
    {
        bool returnVar = false;
        if (!cin) {
            cout << "Вводите только цифры!" << endl;
            cin.clear(); //сбрасывает флаги ошибок,
            while (cin.get() != '\n'); //возвращает последний символ из потока.
            returnVar = true;
        }
        return returnVar;
    }
    void printStudents(Student* students, int size);
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