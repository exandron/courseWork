#include "Students.h"
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>

Students::Students() {}

Students::~Students() {
    students.clear();
}

void Students::printInfo() {
    cout << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << "|   �� - ����� �������� (1 - ����., 0 - ��.)              |" << endl;
    cout << "|   �� - ������� ������� � ���. ����� (1 - ��, 0 - ���)   |" << endl;
    cout << "|   ��� ������� � ���������:                              |" << endl;
    cout << "|   01 - ��                                               |" << endl;
    cout << "|   02 - ��                                               |" << endl;
    cout << "|   03 - ������                                           |" << endl;
    cout << "|   05 - ������� ��������                                 |" << endl;
    cout << "|   06 - ������                                           |" << endl;
    cout << "|   07 - �����������                                      |" << endl;
    cout << "|   08 - ����                                             |" << endl;
    cout << "|   09 - ����                                             |" << endl;
    cout << "|   10 - �����                                            |" << endl;
    cout << "|   11 - ������                                           |" << endl;
    cout << "|   12 - ���                                              |" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << endl;
}

int Students::getSizeFromFile(string filename) {
    ifstream file;
    file.open(filename);
    string line;
    int size = 0;
    if (file.is_open()) {
        if (file.peek() == EOF) {
            return 0;
        }
        while (!file.eof()) {
            size++;
            getline(file, line);
        }
    }
    else {
        cout << "���� �� ������ !" << endl;
    }
    file.close();
    return size;
}

void Students::readStudentsFromFile(string filename) {
    ifstream file;
    file.open(filename);
    //students.clear();
    if (file.is_open()) {
        Student student;
        for (int i = 0; i < getSizeFromFile(filename); i++) {
            file >> student;
            students.push_back(student);
        }
    }
    else {
        cout << "���� �� ������ !" << endl;
    }
    file.close();
}

void Students::writeStudentsIntoFile(string filename) {
    ofstream file1;
    file1.open(filename);
    if (file1.is_open()) {
        for (int i = 0; i < students.size(); i++) {
            file1 << students[i];
            if (i != students.size() - 1) {
                file1 << endl;
            }
        }
    }
    else {
        cout << "���� �� ������ !" << endl;
    }
    file1.close();
}

void Students::addStudent() {
    students.push_back(inputStudentInformation());
    cout << "������� ������� ��������!" << endl;
}

void Students::editStudent() {
    cout << "������� ����� ��������, �������� ������ ���������������: " << endl;
    int number;
    cin >> number;
    string input;
    int input1;
    isSymbolic(number);
    if (number > 0 && number <= students.size()) {
        cout << "����� �������� �� ������ ���������������?" << endl;
        cout << " 1 - �������" << endl;
        cout << " 2 - ���" << endl;
        cout << " 3 - ��������" << endl;
        cout << " 4 - ������" << endl;
        cout << " 5 - ������� ������� � ���. �����" << endl;
        cout << " 6 - ����� ��������" << endl;
        cout << " 7 - ������" << endl;
        cout << " 8 - ������ �� ��������" << endl;
        cout << " 0 - ��������� � ����" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "������� �������: " << endl;
            getchar();
            getline(cin, input, '\n');
            students[number - 1].setSurname(input);
            break;
        case 2:
            cout << "������� ���: " << endl;
            getchar();
            getline(cin, input, '\n');
            students[number - 1].setName(input);
            break;
        case 3:
            cout << "������� ��������: " << endl;
            getchar();
            getline(cin, input, '\n');
            students[number - 1].setFathername(input);
            break;
        case 4:
            cout << "������� ����� ������: " << endl;
            cin >> input1;
            while (isSymbolic(input1) == true) {
                cout << "������� ����� ������: " << endl;
                cin >> input1;
            }
            students[number - 1].setGroup(input1);
            break;
        case 5:
            cout << "������� 1 - ������� � ��� �����; 0 - ���������: " << endl;
            cin >> input1;
            while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
                cout << "������������ ����! ��������� �������." << endl;
                cout << "������� 1 - ������� � ��� �����; 0 - ���������: " << endl;
                cin >> input1;
            }
            students[number - 1].setSocialLife(input1 != 0);
            break;
        case 6:
            cout << "������� 1 - ��������� ����� ��������; 0 - ������� ����� ��������: " << endl;
            cin >> input1;
            while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
                cout << "������������ ����! ��������� �������." << endl;
                cout << "������� 1 - ��������� ����� ��������; 0 - ������� ����� ��������: " << endl;
                cin >> input1;
            }
            students[number - 1].setFormOfEducation(input1 != 0);
            break;
        case 0: break;
        default: cout << "�������� ����." << endl;
        }
        cout << "�������������� ������ ������ �������!" << endl;
    }
    else {
        cout << "��� ������ ������ ��������." << endl;
        cout << "������� ����� �������� ��������: " << endl;
        editStudent();
    }
}

Student Students::inputStudentInformation() {
    printInfo();
    Student newStudent;
    string input;
    int input1;
    cout << "������� �������: " << endl;
    getchar();
    getline(cin, input, '\n');
    newStudent.setSurname(input);
    cout << "������� ���: " << endl;
    getchar();
    getline(cin, input, '\n');
    newStudent.setName(input);
    cout << "������� ��������: " << endl;
    getchar();
    getline(cin, input, '\n');
    newStudent.setFathername(input);
    cout << "������� ����� ������: " << endl;
    cin >> input1;
    while (isSymbolic(input1) == true) {
        cout << "������� ����� ������: " << endl;
        cin >> input1;
    }
    newStudent.setGroup(input1);
    cout << "������� 1 - ������� � ��� �����; 0 - ���������: " << endl;
    cin >> input1;
    while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
        cout << "������������ ����! ��������� �������." << endl;
        cout << "������� 1 - ������� � ��� �����; 0 - ���������: " << endl;
        cin >> input1;
    }
    newStudent.setSocialLife(input1 != 0);
    cout << "������� 1 - ��������� ����� ��������; 0 - ������� ����� ��������: " << endl;
    cin >> input1;
    while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
        cout << "������������ ����! ��������� �������." << endl;
        cout << "������� 1 - ��������� ����� ��������; 0 - ������� ����� ��������: " << endl;
        cin >> input1;
    }
    newStudent.setFormOfEducation(input1 != 0);
    vector<Test> tests;
    vector<Exam> exams;
    for (int i = 0; i < 9; i++) {
        if (i < 5) {
            Test test;
            cout << "����� " << i + 1 << ":\n   ������� ��� ��������: ";
            cin >> input;
            test.setName(input);
            cout << "   ������� 1 - �����, 0 - �������, -1 - �� ����: ";
            cin >> input1;
            while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
                cout << "������������ ����! ��������� �������." << endl;
                cout << "   ������� 1 - �����, 0 - �������, -1 - �� ����: " << endl;
                cin >> input1;
            }
            if (input1 != -1) {
                test.setGrade(input1);
                while (!isDate(input)) {
                    cout << "   ������� ���� ������ � ������� ����/�����/���: ";
                    cin >> input;
                }
                size_t pos = 0;
                string delimiter = "/";
                MyDate newDate;
                input += delimiter;
                for (int j = 0; (pos = input.find(delimiter)) != string::npos; j++) {
                    string token = input.substr(0, pos);
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
                    input.erase(0, pos + delimiter.length());
                }
                test.setDate(newDate);
            }
            tests.push_back(test);
        }
        else {
            Exam exam;
            cout << "������� " << i - 4 << ":\n   ������� ��� ��������: ";
            cin >> input;
            exam.setName(input);
            cout << "   ������� ������ ��� -1, ���� �������� ��� �� ����: ";
            cin >> input1;
            while (isSymbolic(input1) == true || input1 > 10 || input1 < -1) {
                cout << "������������ ����! ��������� �������." << endl;
                cout << "   ������� ������ ��� -1, ���� �������� ��� �� ����: " << endl;
                cin >> input1;
            }
            if (input1 != -1) {
                exam.setGrade(input1);
                cout << "   ������� ���� �������� � ������� ����/�����/���: ";
                cin >> input;
                size_t pos = 0;
                string delimiter = "/";
                MyDate newDate;
                input += delimiter;
                for (int j = 0; (pos = input.find(delimiter)) != string::npos; j++) {
                    string token = input.substr(0, pos);
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
                    input.erase(0, pos + delimiter.length());
                }
                exam.setDate(newDate);
            }
            exams.push_back(exam);
        }
    }
    newStudent.setExams(exams);
    newStudent.setTests(tests);
    return newStudent;
}

void Students::deleteStudent() {
    printStudents(students, students.size());
    int number;
    while (true) {
        cout << "������� ����� ��������, �������� ������ ������� (0 - ��������� � ����): ";
        cin >> number;
        while (isSymbolic(number) == true) {
            cin >> number;
        }
        if (number == 0) {
            return;
        }
        else {
            break;
        }
    }
    cout << "�� ������������� ������ ������� ��������?" << endl;
    cout << "1 - ��" << endl;
    cout << "2 - ���" << endl;
    cout << "0 - �����" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            if (number > 0 && number <= students.size()) {
                students.erase(students.begin() + number - 1);
                cout << "�������� ������ �������!" << endl;
                break;
            }
            else {
                cout << "��� ������ ������ ��������." << endl;
                deleteStudent();
            }
        case 2: deleteStudent();
            break;
        case 0: return;
        default: cout << "������� ����� ���������." << endl;
    }
}

void Students::searchStudent() {
    cout << endl;
    cout << "��������� ��� ������ ���������: " << endl;
    cout << "1 - ������" << endl;
    cout << "2 - �������" << endl;
    cout << "3 - ���" << endl;
    cout << "4 - ��������" << endl;
    cout << "5 - ����� ��������" << endl;
    cout << "6 - ���������� �����" << endl;
    cout << "0 - ��������� �����" << endl;
    cout << endl;
    cout << "��� �����: ";
    int choice;
    cin >> choice;
    while (choice > 4 || choice < 0) {
        cout << "������� ������ �����: " << endl;
        cin >> choice;
    }
    string input;
    switch (choice) {
    case 1:
        cout << "������� ����� ������: " << endl;
        break;
    case 2:
        cout << "������� ������� ��������: " << endl;
        break;
    case 3:
        cout << "������� ��� ��������: " << endl;
        break;
    case 4:
        cout << "������� �������� ��������: " << endl;
        break;
    case 5:
        cout << "������� 1 - ��������� ����� ��������; 0 - ������� ����� ��������" << endl;
        break;
    case 6:
        cout << "������� 1 - ������� � ��� �����; 0 - ���������: " << endl;
        break;
    case 0: return;
    default: cout << "�������� ����!" << endl;
    }
    cin >> input;
    vector<Student> searchedStudents;
    for (int i = 0; i < students.size(); i++) {
        switch (choice) {
        case 1:
            if (students[i].getGroup() == stoi(input)) {
                searchedStudents.push_back(students[i]);
            }
            break;
        case 2:
            if (students[i].getSurname() == input) {
                searchedStudents.push_back(students[i]);
            }
            break;
        case 3:
            if (students[i].getName() == input) {
                searchedStudents.push_back(students[i]);
            }
            break;
        case 4:
            if (students[i].getFathername() == input) {
                searchedStudents.push_back(students[i]);
            }
            break;
        case 5:
            if (students[i].getFormOfEducation() == stoi(input)) {
                searchedStudents.push_back(students[i]);
            }
            break;
        case 6:
            if (students[i].getSocialLife() == stoi(input)) {
                searchedStudents.push_back(students[i]);
            }
            break;
        case 0: break;
        default:  return;
        }
    }
    printStudents(searchedStudents, searchedStudents.size());
}

void Students::filterStudents() {
    setlocale(LC_CTYPE, "Russian");
    cout << endl;
    cout << "1 - ���������� �����" << endl;
    cout << "2 - �������" << endl;
    cout << "3 - ������� ����" << endl;
    cout << "0 - ��������� �����" << endl;
    cout << endl;
    cout << "������� ����� ����, �� �������� ���������� ������������� ���������: ";
    int choice;
    cin >> choice;
    while (choice > 3 || choice < 0) {
        cout << "������� ������ �����: " << endl;
        cin >> choice;
    }
    int input1;
    int input2;
    double inp1;
    double inp2;
    string surname;
    char firstLetter;
    char lastLetter;
    vector<Student> filteredStudents;
    switch (choice) {
    case 1:
        cout << "������� ��������� �����: " << endl;
        cin >> input1;
        cout << "������� �������� �����: " << endl;
        cin >> input2;
        for ( int i = input1 - 1; i < input2; i++) {
                filteredStudents.push_back(students[i]);
        }
        printStudents(filteredStudents, filteredStudents.size());
        break;
    case 2:
        cout << "�������, � ����� ����� �������� �������: " << endl;
        cin >> firstLetter;
        cout << "�������, �� ����� ����� �������� ���������: " << endl;
        cin >> lastLetter;
        cout << (char)toupper(firstLetter);
        for (int i = 0; i < students.size(); i++) {
            surname = students[i].getSurname();
            if ((surname[0] >= firstLetter || surname[0] >= (char)toupper(firstLetter)) && (surname[0] <= lastLetter || surname[0] <= (char)toupper(lastLetter))){
                    filteredStudents.push_back(students[i]);
            }
        }
        printStudents(filteredStudents, filteredStudents.size());
        break;
    case 3:
        cout << "������� ��������� ������� ����: " << endl;
        cin >> inp1;
        cout << "������� �������� ������� ����: " << endl;
        cin >> inp2;
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getMiddleGrade() >= inp1 && students[i].getMiddleGrade() <= inp2) {
                filteredStudents.push_back(students[i]);
            }
        }
        printSortedStudents(filteredStudents, filteredStudents.size());
        break;
    case 0: return;
    default: return;
    }
}   

void Students::getScholarshipStat() {
    cout << "������� ������� ���������: ";
    double scholarship;
    cin >> scholarship;
    cout << "+---+----------------+---------------+-------------------+------------------------+----------+" << endl;
    cout << "| � |     �������    |      ���      |      ��������     |  ������ ���������(BYN) | ��. ���� |" << endl;
    cout << "+---+----------------+---------------+-------------------+------------------------+----------+" << endl;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getFormOfEducation() == 1) {
            cout << left << "| " << setw(2) << i + 1;
            cout << "| " << setw(15) << students[i].getSurname() << "| "
                << setw(14) << students[i].getName() << "| " << setw(18) << students[i].getFathername() << "|  ";
            if (students[i].getScholarship(scholarship) < 0) {
                cout << left << setw(22) << "�� ����� ������" << "|  " << setw(8) << students[i].getMiddleGrade() << "|" << endl; ;
            }
            else {
                cout << left << setw(22) << students[i].getScholarship(scholarship) << "|  " << setw(8) << students[i].getMiddleGrade() << "|" << endl;
            }
            cout << "+---+----------------+---------------+-------------------+------------------------+----------+" << endl;
        }
    }
}

void Students::sortStudents() {
    cout << endl;
    cout << "1 - �������" << endl;
    cout << "2 - ����� ��������" << endl;
    cout << "3 - ���������� �����" << endl;
    cout << "4 - ������� ����" << endl;
    cout << "0 - ��������� �����" << endl;
    cout << endl;

    cout << "�������� ����, �� �������� ����������� ����������: " << endl;
    int choice1;
    cin >> choice1;
    isSymbolic(choice1);
    while (choice1 < 0 || choice1>4) {
        cout << "������� ������ �����!" << endl;
        cin >> choice1;
    }
    if (choice1 == 0) {
        return;
    }
    cout << "�������� ��� ���������� " << endl;
    cout << "1 - �� �����������" << endl;
    cout << "2 - �� ��������" << endl;
    int choice2;
    cin >> choice2;
    isSymbolic(choice2);
    if (choice2 > 2 || choice2 < 1) {
        cout << "������� ������ �����!" << endl;
        return;
    }
    sortStudentsByOption(choice1, choice2);
}

void Students::sortStudentsByOption(int option, int sort) {
    vector<Student> sortedStudents;
    for (int i = 0; i < students.size(); i++) {
        sortedStudents.push_back(students[i]);
    }
    Student temp;
    int count = 0;
    switch (option) {
    case 1:
        for (int i = 0; i < students.size() - 1; i++) {
            for (int j = 0; j < students.size() - i - 1; j++) {
                if (sort == 1 && strcmp(sortedStudents[j].getSurname().c_str(), sortedStudents[j + 1].getSurname().c_str()) > 0) {
                    temp = sortedStudents[j];
                    sortedStudents[j] = sortedStudents[j + 1];
                    sortedStudents[j + 1] = temp;
                }
                if (sort == 2 && strcmp(sortedStudents[j].getSurname().c_str(), sortedStudents[j + 1].getSurname().c_str()) < 0) {
                    temp = sortedStudents[j];
                    sortedStudents[j] = sortedStudents[j + 1];
                    sortedStudents[j + 1] = temp;
                }
            }
        }
        printStudents(sortedStudents, students.size());
        break;
    case 2:
        for (int i = 0; i < students.size(); i++) {
            if (sort == 1 && !students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        for (int i = 0; i < students.size(); i++) {
            if (sort == 1 && students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && !students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        printStudents(sortedStudents, students.size());
        break;
    case 3:
        for (int i = 0; i < students.size(); i++) {
            if (sort == 1 && !students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        for (int i = 0; i < students.size(); i++) {
            if (sort == 1 && students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && !students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        printStudents(sortedStudents, students.size());
        break;
    case 4:
        for (int i = 0; i < students.size() - 1; i++) {
            for (int j = 0; j < students.size() - i - 1; j++) {
                if (sort == 1 && sortedStudents[j].getMiddleGrade() > sortedStudents[j + 1].getMiddleGrade()) {
                    temp = sortedStudents[j];
                    sortedStudents[j] = sortedStudents[j + 1];
                    sortedStudents[j + 1] = temp;
                }
                if (sort == 2 && sortedStudents[j].getMiddleGrade() < sortedStudents[j + 1].getMiddleGrade()) {
                    temp = sortedStudents[j];
                    sortedStudents[j] = sortedStudents[j + 1];
                    sortedStudents[j + 1] = temp;
                }
            }
        }
        printSortedStudents(sortedStudents, students.size());
        break;
    case 0: break; return;
    default: cout << "������� ������ �����!" << endl;
        break; return;
        
    }
}

void Students::printSortedStudents(vector<Student> students, int size) {
    if (size == 0) {
        cout << "��� ������� � ���������!" << endl;
    }
    else {
        cout << "+---+----------------+---------------+-------------------+--------------+" << endl;
        cout << "| � |     �������    |      ���      |      ��������     | ������� ���� |" << endl;
        cout << "+---+----------------+---------------+-------------------+--------------+" << endl;
        for (int i = 0; i < students.size(); i++) {
            cout << left << "| " << setw(2) << i + 1;
            cout << "| " << setw(15) << students[i].getSurname() << "| "
                << setw(14) << students[i].getName() << "| " << setw(18) << students[i].getFathername() << "|  " << right << setw(9) << students[i].getMiddleGrade() << "   |" << endl; ;
        }
        cout << "+---+----------------+---------------+-------------------+--------------+" << endl;
    }
}

void Students::printStudents(vector<Student> students, int size) {

    if (size == 0) {
        cout << "��� ������� � ���������!" << endl;
    }
    else {

        cout << "+---+-------+----------------+---------------+-------------------+----+----+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;
        cout << "| � | � ��. |     �������    |      ���      |      ��������     | �� | �� | ��� 1, ���� | ��� 2, ���� | ��� 3, ���� | ��� 4, ���� | ��� 5, ���� | ��� 1, ���� | ��� 2, ���� | ��� 3, ���� | ��� 4, ���� |" << endl;
        cout << "+---+-------+----------------+---------------+-------------------+----+----+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;
        for (int i = 0; i < size; i++) {
            cout << left << "| " << setw(2) << i + 1 << "| " << setw(6) << students[i].getGroup() << "| " << setw(15) << students[i].getSurname() << "| "
                << setw(14) << students[i].getName() << "| " << setw(18) << students[i].getFathername() << "|  " << setw(2)
                << students[i].getFormOfEducation() << "|  " << setw(2) << students[i].getSocialLife() << "|";
            for (int j = 0; j < 5; j++) {
                string line = students[i].getTests()[j].getName() + ", ";
                string tmp = "";
                if (!students[i].getTests()[j].isHappened()) {
                    line += "-";
                    tmp += "";
                }
                else {
                    if (students[i].getTests()[j].getGrade()) {
                        line += "���";
                    }
                    else {
                        line += "�����";
                    }
                }
                cout << left << " " << setw(12) << line << tmp << "|";
            }
            for (int j = 0; j < 4; j++) {
                string line = students[i].getExams()[j].getName() + ", ";
                string tmp = "";
                if (!students[i].getExams()[j].isHappened()) {
                    line += "-";
                    tmp += "";
                }
                else {
                    line += to_string(students[i].getExams()[j].getGrade());
                }
                cout << left << " " << setw(12) << line << tmp << "|";
            }
            cout << endl;
        }
        cout << "+---+-------+----------------+---------------+-------------------+----+----+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;
    }
}