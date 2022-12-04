#include "Students.h"
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

Students::Students() {
    size = 0;
    students = new Student[size];
}

Students::Students(int size) {
    this->size = size;
    students = new Student[size];
}

Students::~Students() {
    delete[] students;
}

void Students::printInfo() {
    cout << "ФО - форма обучения (1 - бюдж., 0 - пл.)" << endl;
    cout << "СЖ - признак участия в соц. жизни (1 - да, 0 - нет)" << endl;
    cout << "Код зачетов и экзаменов: " << endl;
    cout << "01 - МА " << endl;
    cout << "02 - ДМ " << endl;
    cout << "03 - Физика " << endl;
    cout << "05 - История Беларуси " << endl;
    cout << "06 - Логика " << endl;
    cout << "07 - Политология " << endl;
    cout << "08 - ОАиП " << endl;
    cout << "09 - ТРПО " << endl;
    cout << "10 - ООПиП " << endl;
    cout << "11 - ОКПрог " << endl;
    cout << "12 - ОКГ " << endl;
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
        cout << "Файл не открыт !" << endl;
    }
    file.close();

    return size;
}

void Students::readStudentsFromFile(string filename) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            file >> students[i];
        }
    }
    else {
        cout << "Файл не открыт !" << endl;
    }
    file.close();
}

void Students::writeStudentsIntoFile(string filename) {
    ofstream file1;
    file1.open(filename);
    if (file1.is_open()) {
        for (int i = 0; i < size; i++) {
            file1 << students[i];
            if (i != size - 1) {
                file1 << endl;
            }
        }
    }
    else {
        cout << "Файл не открыт !" << endl;
    }
    file1.close();
}

void Students::addStudent() {
    Student* newStudents = new Student[size + 1];
    for (int i = 0; i < size; i++) {
        newStudents[i] = students[i];
    }
    newStudents[size] = inputStudentInformation();
    delete[] students;
    size++;
    students = newStudents;
    cout << "Студент успешно дабавлен!" << endl;
}

void Students::editStudent() {
    cout << "Введите номер студента, которого хотите отредактировать: " << endl;
    int number;
    cin >> number;
    isSymbolic(number);
    if (number > 0 && number <= size) {
        students[number - 1] = inputStudentInformation();
    }
    else {
        cout << "Нет такого номера студента." << endl;
        cout << "Введите номер студента повторно: " << endl;
        editStudent();
    }
}

Student Students::inputStudentInformation() {
    printInfo();
    Student newStudent;
    string input;
    int input1;
    cout << "Введите фамилию: " << endl;
    cin >> input;
    getline(cin, input);
    newStudent.setSurname(input);
    cout << "Введите имя: " << endl;
    cin >> input;
    getline(cin, input);
    newStudent.setName(input);
    cout << "Введите отчество: " << endl;
    cin >> input;
    getline(cin, input);
    newStudent.setFathername(input);
    cout << "Введите номер группы: " << endl;
    cin >> input1;
    while (isSymbolic(input1) == true) {
        cout << "Введите номер группы: " << endl;
        cin >> input1;
    }
    newStudent.setGroup(input1);
    cout << "Введите 1 - участие в соц жизни; 0 - неучастие: " << endl;
    cin >> input1;
    while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
        cout << "Некорректный ввод! Повторите попытку." << endl;
        cout << "Введите 1 - участие в соц жизни; 0 - неучастие: " << endl;
        cin >> input1;
    }
    newStudent.setSocialLife(input1 != 0);
    cout << "Введите 1 - бюджетная форма обучения; 0 - платная форма обучения: " << endl;
    cin >> input1;
    while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
        cout << "Некорректный ввод! Повторите попытку." << endl;
        cout << "Введите 1 - бюджетная форма обучения; 0 - платная форма обучения: " << endl;
        cin >> input1;
    }
    newStudent.setFormOfEducation(input1 != 0);
    for (int i = 0; i < 9; i++) {
        if (i < 5) {
            cout << "Зачет " << i + 1 << ":\n   Введите код предмета: ";
            cin >> input;
            newStudent.getTests()[i].setName(input);
            cout << "   Введите 1 - зачет, 0 - незачет, -1 - не сдан: ";
            cin >> input1;
            while (isSymbolic(input1) == true || input1 > 1 || input1 < -1) {
                cout << "Некорректный ввод! Повторите попытку." << endl;
                cout << "   Введите 1 - зачет, 0 - незачет, -1 - не сдан: " << endl;
                cin >> input1;
            }
            if (input1 != -1) {
                newStudent.getTests()[i].setIsPassed(input1);
                while (!isDate(input)) {
                    cout << "   Введите дату зачета в формате день/месяц/год: ";
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
                newStudent.getTests()[i].setDate(newDate);
            }
        }
        else {
            cout << "Экзамен " << i - 4 << ":\n   Введите код предмета: ";
            cin >> input;
            newStudent.getExams()[i - 5].setName(input);
            cout << "   Введите оценку или -1, если экзамен не сдан: ";
            cin >> input1;
            while (isSymbolic(input1) == true || input1 > 10 || input1 < -1) {
                cout << "Некорректный ввод! Повторите попытку." << endl;
                cout << "   Введите оценку или -1, если экзамен не сдан: " << endl;
                cin >> input1;
            }
            if (input1 != -1) {
                newStudent.getExams()[i - 5].setGrade(input1);
                cout << "   Введите дату экзамена в формате день/месяц/год: ";
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
                newStudent.getExams()[i - 5].setDate(newDate);
            }
        }
    }
    return newStudent;
}

void Students::deleteStudent() {
        cout << "Введите номер студента, которого хотите удалить: ";
        int number;
        cin >> number;
        while (isSymbolic(number) == true) {
            cin >> number;
        }
        cout << "Вы действительно хотите удалить студента?" << endl;
        cout << "1 - Да" << endl;
        cout << "2 - Нет" << endl;
        cout << "0 - Выход" << endl;
        int choice;
        cin >> choice;
        Student* newStudents = new Student[size - 1];
        switch (choice) {
        case 1:
            if (number > 0 && number <= size) {
                for (int i = 0; i < number - 1; i++) {
                    newStudents[i] = students[i];
                }
                for (int i = number; i < size; i++) {
                    newStudents[i - 1] = students[i];
                }
                delete[] students;
                size--;
                students = newStudents;
                cout << "Удаление прошло успешно!" << endl;
                break;
            }
            else {
                cout << "Нет такого номера студента." << endl;
                deleteStudent();
            }
        case 2: deleteStudent();
            break;
        case 0: return;
        default: cout << "Введите число правильно." << endl;
        }
}

void Students::searchStudent() {
    cout << "1 - Группа" << endl;
    cout << "2 - Фамилия" << endl;
    cout << "3 - Форма обучения" << endl;
    cout << "4 - Социальная жизнь" << endl;
    cout << "0 - Вернуться назад" << endl;
    cout << "Введите номер поля, по которому вы хотите найти студента: ";
    int choice;
    cin >> choice;
    while (choice > 4 || choice <0) {
        cout << "Введите верное число: " << endl;
        cin >> choice;
    }
    string input;
    switch (choice) {
    case 1:
        cout << "Введите номер группы: " << endl;
        break;
    case 2:
        cout << "Введите фамилию студента: " << endl;
        break;
    case 3:
        cout << "Введите 1 - бюджетная форма обучения; 0 - платная форма обучения" << endl;
        break;
    case 4:
        cout << "Введите 1 -участие в соц жизни; 0 - неучастие: " << endl;
        break;
    case 0: return;
    default: return;
        
    }
    cin >> input;
    Student* searchedStudents = new Student[size];
    int count = 0;
    for (int i = 0; i < size; i++) {
        switch (choice) {
        case 1:
            if (students[i].getGroup() == stoi(input)) {
                searchedStudents[count] = students[i];
                count++;
            }
            break;
        case 2:
            if (students[i].getSurname() == input) {
                searchedStudents[count] = students[i];
                count++;
            }
            break;
        case 3:
            if (students[i].getFormOfEducation() == stoi(input)) {
                searchedStudents[count] = students[i];
                count++;
            }
            break;
        case 4:
            if (students[i].getSocialLife() == stoi(input)) {
                searchedStudents[count] = students[i];
                count++;
            }
            break;
        case 0: break; return;
        default:  return;
        }
    }
    Student* newSearchedStudents = new Student[count];
    for (int i = 0; i < count; i++) {
        newSearchedStudents[i] = searchedStudents[i];
    }
    delete[] searchedStudents;
    printStudents(newSearchedStudents, count);
}

void Students::getScholarshipStat() {
    cout << "Введите базовую стипендию: ";
    double scholarship;
    cin >> scholarship;
    cout << "+---+----------------+---------------+-------------------+------------------------+----------+" << endl;
    cout << "| № |     Фамилия    |      Имя      |      Отчество     |  Размер стипендии(BYN) | Ср. балл |" << endl;
    cout << "+---+----------------+---------------+-------------------+------------------------+----------+" << endl;
    for (int i = 0; i < size; i++) {
        if (students[i].getFormOfEducation() == 1) {
        cout << left << "| " <<setw(2)  << i + 1;
            cout << "| " << setw(15) << students[i].getSurname() << "| "
                << setw(14) << students[i].getName() << "| " << setw(18) << students[i].getFathername() << "|  ";
            if (students[i].getScholarship(scholarship) < 0) {
                cout <<left<< setw(22)<< "не сдана сессия"<< "|  " << setw(8) << students[i].getMiddleGrade() << "|" << endl; ;
            }
            else {
                cout << left<<setw(22) << students[i].getScholarship(scholarship)<< "|  " << setw(8) <<students[i].getMiddleGrade()<<"|"<<endl;
            }
            cout << "+---+----------------+---------------+-------------------+------------------------+----------+" << endl;
        }
    }
}

void Students::sortStudents() {
    cout << "1 - Фамилия" << endl;
    cout << "2 - Форма обучения" << endl;
    cout << "3 - Социальная жизнь" << endl;
    cout << "4 - Средний балл" << endl;
    cout << "0 - Вернуться назад" << endl;
  
    cout << "Выберите поле, по которому производить сортировку: " << endl;
    int choice1;
    cin >> choice1;
    isSymbolic(choice1);
    while (choice1 < 0 || choice1>4) {
        cout << "Введите верное число!" << endl;
        cin >> choice1;
    }
    if (choice1 == 0) {
        return;
    }
    cout << "Выберите вид сортировки " << endl;
    cout << "1 - По возрастанию" << endl;
    cout << "2 - По убыванию" << endl;
    int choice2;
    cin >> choice2;
    isSymbolic(choice2);
    if (choice2 > 2 || choice2 < 1) {
        cout << "Введите верное число!" << endl;
        return;
    }
    sortStudentsByOption(choice1, choice2);
}

void Students::sortStudentsByOption(int option, int sort) {
    Student* sortedStudents = new Student[size];
    for (int i = 0; i < size; i++) {
        sortedStudents[i] = students[i];
    }
    Student temp;
    int count = 0;
    switch (option) {
    case 1:
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
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
        printStudents(sortedStudents, size);
        break;
    case 2:
        for (int i = 0; i < size; i++) {
            if (sort == 1 && !students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        for (int i = 0; i < size; i++) {
            if (sort == 1 && students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && !students[i].getFormOfEducation()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        printStudents(sortedStudents, size);
        break;
    case 3:
        for (int i = 0; i < size; i++) {
            if (sort == 1 && !students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        for (int i = 0; i < size; i++) {
            if (sort == 1 && students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
            if (sort == 2 && !students[i].getSocialLife()) {
                sortedStudents[count] = students[i];
                count++;
            }
        }
        printStudents(sortedStudents, size);
        break;
    case 4:
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
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
       printStudents(sortedStudents, size);
       break;
    case 0: break; return;
    default: cout << "Введите верное число!" << endl;
        break; return;
    }
}

void Students::printStudents(Student *students, int size) {

    if (size == 0) {
        cout << "Нет записей о студентах!" << endl;
    }
    else {

        cout << "+---+-------+----------------+---------------+-------------------+----+----+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;
        cout << "| № | № гр. |     Фамилия    |      Имя      |      Отчество     | ФО | СЖ | Зач 1, итог | Зач 2, итог | Зач 3, итог | Зач 4, итог | Зач 5, итог | Экз 1, итог | Экз 2, итог | Экз 3, итог | Экз 4, итог |" << endl;
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
                    if (students[i].getTests()[j].getIsPassed()) {
                        line += "зач";
                    }
                    else {
                        line += "незач";
                        tmp += " ";
                    }
                }
                cout << left << " " << setw(12) << line << tmp << "|";
            }
            for (int j = 0; j < 4; j++) {
                string line = students[i].getExams()[j].getName() + ", ";
                string tmp = "";
                if (!students[i].getExams()[j].isHappened()) {
                    line += "-";
                    tmp += " ";
                }
                else {
                    line += to_string(students[i].getExams()[j].getGrade());
                }
                cout << left << " " << setw(12) << line << tmp << "|";
            }
            cout << endl;
            cout << "+---+-------+----------------+---------------+-------------------+----+----+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;
        }
    }
}




