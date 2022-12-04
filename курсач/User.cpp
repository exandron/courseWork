#include "User.h"
#include "Students.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <vector>

User::User() {
    login = "";
    password = "";
    isAdmin = false;
    usersAmount = 0;
    users = new User[usersAmount];
}

User::User(string login, string password, bool isAdmin, User* users, int usersAmount) {
    this->login = login;
    this->password = password;
    this->isAdmin = isAdmin;
    this->usersAmount = usersAmount;
    this->users = new User[usersAmount];
    for (int i = 0; i < usersAmount; i++) {
        this->users[i] = users[i];
    }
}

string User::getLogin() {
    return login;
}

string User::getPassword() {
    return password;
}

bool User::getIsAdmin() {
    return isAdmin;
}

void User::setLogin(string login) {
    this->login = login;
}

void User::setPassword(string password) {
    this->password = password;
}

void User::setIsAdmin(bool isAdmin) {
    this->isAdmin = isAdmin;
}

void User::registerUser(string filename) {
    if (isAdmin) {
        int size = usersAmount;
        string* logins = new string[size];
        ifstream file;
        file.open(filename);
        string line;
        if (file.is_open()) {
            for (int j = 0; !file.eof(); j++) {
                getline(file, line);
                size_t pos = 0;
                string delimiter = ";";
                for (int i = 0; (pos = line.find(delimiter)) != string::npos; i++) {
                    string token = line.substr(0, pos);
                    if (i == 0) {
                        logins[j] = token;
                    }
                    line.erase(0, pos + delimiter.length());
                }
            }
        }
        else {
            cout << "Файл не открыт !" << endl;
        }
        file.close();

        cout << "Введите логин: ";
        string login;
        cin >> login;
        for (int i = 0; i < size; i++) {
            if (strcmp(login.c_str(), logins[i].c_str()) == 0) {
                cout << "Данный логин уже занят!";
                return;
            }
        }
        cout << "Введите пароль: ";
        string password = inputPassword();
        cout << "Желаете ли сделать данного пользователя администратором?\n1 - Да\n0 - Нет\n";
        int choice;
        while (true) {
            cin >> choice;
            if (choice == 1 || choice == 0) {
                break;
            }
            else {
                cout << "Введено неправильное значение! Повторите попытку: ";
            }
        }
        ofstream file1;
        file1.open(filename, ios::app);
        if (file1.is_open()) {
            file1 << endl << login << ";" << password << ";" << choice << ";";
        }
        else {
            cout << "Файл не открыт !" << endl;
        }
        file1.close();
        getUsersFromFile(filename);
    }
    else {
        cout << "У вас нет доступа!\n";
        return;
    }
}

bool User::loginIntoSystem(string filename) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        if (file.peek() == EOF) {
            cout << "Не существует учетных записей! Требуется зарегистрировать первого администратора!\nВведите логин: ";
            string loginInput;
            cin >> loginInput;
            cout << "Введите пароль: ";
            string password = inputPassword();
            cout << "Администратор успешно зарегистрирован!\n";
            this->login = loginInput;
            this->password = password;
            this->isAdmin = true;
        }
        else {
            bool flag = false;
            for (int i = 0; true; i++) {
                string line;
                string loginInput;
                cout << "Введите логин: ";
                cin >> loginInput;
                string loginTest = loginInput + ";";
                while (!file.eof()) {
                    getline(file, line);
                    if (line.find(loginTest) == 0) {
                        this->login = loginInput;
                        for (int j = 0; true; j++) {
                            cout << "Введите пароль: ";
                            size_t pos = 0;
                            string delimiter = ";";
                            string password = inputPassword();
                            string lineTmp = line;
                            for (int k = 0; (pos = lineTmp.find(delimiter)) != string::npos; k++) {
                                string token = lineTmp.substr(0, pos);
                                if (k == 1 && strcmp(password.c_str(), token.c_str()) != 0) {
                                    if (j != 2) {
                                        cout << "\nНеверный пароль! Повторите попытку!" << endl;
                                        break;
                                    }
                                    else {
                                        cout << "\nНеверный пароль!";
                                        return false;
                                    }
                                }
                                if (k == 2) {
                                    this->password = password;
                                    isAdmin = stoi(token);
                                    getUsersFromFile(filename);
                                    cout << "\nАвторизация успешно выполнена!" << endl;
                                    return true;
                                }
                                lineTmp.erase(0, pos + delimiter.length());
                            }
                        }
                    }
                }
                if (!flag) {
                    if (i < 2) {
                        cout << "\nНеверный логин! Повторите попытку!" << endl;
                        file.close();
                        file.open(filename);
                        continue;
                    }
                    else {
                        cout << "\nНеверный логин!" << endl;
                        return false;
                    }
                }
            }
        }
    }
    else {
        cout << "Файл не открыт !" << endl;
        return false;
    }
    file.close();
    ofstream file1;
    file1.open(filename);
    if (file1.is_open()) {
        file1 << this->login << ";" << this->password << ";" << this->isAdmin << ";";
        return true;
    }
    else {
        cout << "Файл не открыт !" << endl;
        return false;
    }
}

void User::menu(string filepath) {
    string filesname = "students.txt";
    int size = Students::getSizeFromFile(filesname);
    Students students(size);
    students.readStudentsFromFile(filesname);
    if (isAdmin) {
        int choice;
        while (true) {
            cout << "   Меню администатора.  " << endl;
            cout << " 1 -  Добавление студента" << endl;
            cout << " 2 -  Просмотр всех студентов" << endl;
            cout << " 3 -  Редактирование студента" << endl;
            cout << " 4 -  Удаление студента" << endl;
            cout << " 5 -  Сортировка студентов" << endl;
            cout << " 6 -  Поиск студентов" << endl;
            cout << " 7 -  Расчет стипендии студентов-бюджетников" << endl;
            cout << " 8 -  Регистрация пользователя" << endl;
            cout << " 9 -  Просмотр пользователей" << endl;
            cout << " 10 - Редактирование пользователя" << endl;
            cout << " 11 - Удаление пользователя" << endl;
            cout << " 0 -  Выход" << endl;
            cout << "Введите число: ";
            cin >> choice;
            switch (choice) {
            case 1:
                students.addStudent();
                students.writeStudentsIntoFile(filesname);
                break;
            case 2:
                students.printStudents(students.getStudents(), students.getSize());
                break;
            case 3:
                students.editStudent();
                students.writeStudentsIntoFile(filesname);
                break;
            case 4:
                students.deleteStudent();
                students.writeStudentsIntoFile(filesname);
                break;
            case 5:
                students.sortStudents();
                break;
            case 6:
                students.searchStudent();
                break;
            case 7:
                students.getScholarshipStat();
                break;
            case 8:
                registerUser(filepath);
                break;
            case 9:
                printUsers();
                break;
            case 10:
                editUser(filepath);
                break;
            case 11:
                deleteUser(filepath);
                break;
            case 0:
                students.writeStudentsIntoFile(filesname);
                return;
            default:
                cout << "Введено неправильное число!" << endl;
                break;
            }
        }
    }
    else {
        int choice;
        while (true) {
            cout << "   Меню пользователя.  " << endl;
            cout << " 1 -  Просмотр всех студентов" << endl;
            cout << " 2 -  Сортировка студентов" << endl;
            cout << " 3 -  Поиск студентов" << endl;
            cout << " 4 -  Расчет стипендии студентов-бюджетников" << endl;
            cout << " 0 -  Выход" << endl;
            cout << "Введите число: ";
            cin >> choice;
            switch (choice) {
            case 1:
                students.printStudents(students.getStudents(), students.getSize());
                break;
            case 2:
                students.sortStudents();
                break;
            case 3:
                students.searchStudent();
                break;
            case 4:
                students.getScholarshipStat();
                break;
            case 0:
                students.writeStudentsIntoFile(filesname);
                return;
            default:
                cout << "Введено неправильное число!" << endl;
                break;
            }
        }
    }
}

void User::deleteUser(string filepath) {
    printUsers();
    cout << "Введите номер записи, которую хотите удалить: ";
    int choice;
    while (true) {
        cin >> choice;
        if (choice > usersAmount || choice < 1) {
            cout << "Нет такого элемента! Повторите попытку: ";
        }
        else if (getAdminsAmount() == 1 && users[choice - 1].getIsAdmin()) {
            cout << "Вы не можете удалить единственного администратора! Повторите попытку: ";
        }
        else {
            cout << "Данная учетная запись успешно удалена!" << endl;
            break;
        }
    }
    bool exitFlag = false;
    if (users[choice - 1].getLogin() == login) {
        exitFlag = true;
    }
    User* newUsers = new User[usersAmount - 1];
    for (int i = 0; i < choice - 1; i++) {
        newUsers[i] = users[i];
    }
    for (int i = choice; i < usersAmount; i++) {
        newUsers[i - 1] = users[i];
    }
    delete[] users;
    usersAmount--;
    users = newUsers;
    printUsersIntoFile(filepath);
    if (exitFlag) {
        exit(0);
    }
}

void User::editUser(string filepath) {
    printUsers();
    cout << "Введите номер записи, которую хотите изменить: ";
    int choice;
    while (true) {
        cin >> choice;
        if (choice > usersAmount || choice < 1) {
            cout << "Нет такого элемента! Повторите попытку: ";
        }
        else {
            break;
        }
    }
    string* logins = new string[usersAmount];
    ifstream file;
    file.open(filepath);
    string line;
    if (file.is_open()) {
        for (int j = 0; !file.eof(); j++) {
            getline(file, line);
            size_t pos = 0;
            string delimiter = ";";
            for (int i = 0; (pos = line.find(delimiter)) != string::npos; i++) {
                string token = line.substr(0, pos);
                if (i == 0) {
                    logins[j] = token;
                }
                line.erase(0, pos + delimiter.length());
            }
        }
    }
    else {
        cout << "Файл не открыт !" << endl;
    }
    file.close();

    cout << "Введите логин: ";
    string login;
    cin >> login;
    for (int i = 0; i < usersAmount; i++) {
        if (strcmp(login.c_str(), logins[i].c_str()) == 0) {
            cout << "Данный логин уже занят!";
            return;
        }
    }
    cout << "Введите пароль: ";
    string password = inputPassword();
    cout << "Желаете ли сделать данного пользователя администратором?\n1 - Да\n0 - Нет\n";
    int role;
    while (true) {
        cin >> role;
        if (role == 1 || role == 0) {
            cout << "Данная учетная запись успешно отредактирована!" << endl;
            break;
        }
        else {
            cout << "Введено неправильное значение! Повторите попытку: ";
        }
    }
    users[choice - 1].setLogin(login);
    users[choice - 1].setPassword(password);
    users[choice - 1].setIsAdmin(role);
    printUsersIntoFile(filepath);
}

void User::getUsersFromFile(string filename) {
    ifstream file;
    file.open(filename);
    int size = Students::getSizeFromFile(filename);
    usersAmount = size;
    delete[] users;
    users = new User[size];
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            file >> users[i];
        }
    }
    else {
        cout << "Файл не открыт !" << endl;
    }
    file.close();
}

void User::printUsers() {
    cout << "+---+---------------------+--------------------+" << endl;
    cout << "| № |        Логин        |         Роль       |" << endl;
    cout << "+---+---------------------+--------------------+"<< endl;
    for (int i = 0; i < usersAmount; i++) {
        string role = users[i].getIsAdmin() ? "Администратор" : "Пользователь";
        cout << left << "| "<< setw(2) << i + 1 << "|  " << setw(19) << users[i].getLogin() << "|  "<< setw(18) << role << "|" << endl;
        cout << "+---+---------------------+--------------------+" << endl;
    }
}

istream& operator>>(istream& in, User& user) {
    if (in.peek() != EOF) {
        string line;
        getline(in, line);
        size_t pos = 0;
        string delimiter = ";";
        for (int i = 0; (pos = line.find(delimiter)) != string::npos; i++) {
            string token = line.substr(0, pos);
            switch (i) {
            case 0:
                user.setLogin(token);
                break;
            case 1:
                user.setPassword(token);
                break;
            case 2:
                user.setIsAdmin(stoi(token));
                break;
            }
            line.erase(0, pos + delimiter.length());
        }
    }
    return in;
}

void User::printUsersIntoFile(string filename) {
    ofstream file1;
    file1.open(filename);
    if (file1.is_open()) {
        for (int i = 0; i < usersAmount; i++) {
            file1 << users[i].getLogin() << ";" << users[i].getPassword() << ";" << users[i].getIsAdmin() << ";";
            if (i != usersAmount - 1) {
                file1 << endl;
            }
        }
    }
    else {
        cout << "Файл не открыт !" << endl;
    }
    file1.close();
}

int User::getAdminsAmount() {
    int result = 0;
    for (int i = 0; i < usersAmount; i++) {
        if (users[i].getIsAdmin()) {
            result++;
        }
    }
    return result;
}

User* User::getUsers() {
    return users;
}

int User::getUsersAmount() {
    return usersAmount;
}

string User::inputPassword()
{
    while (true)
    {
        string user_password;
        char pass_input;
        size_t delete_code = 8;
        size_t enter_code = 13;
        while (true)
        {
            pass_input = _getch();
            if (pass_input == enter_code)
                break;
            else if (pass_input == delete_code)
            {
                cout << (char)8 << ' ' << (char)8;
                if (!user_password.empty())
                    user_password.erase(user_password.length() - 1);
            }
            else
            {
                cout << "*";
                user_password.push_back(pass_input);
                
            }
           
        }
        return user_password;
    }
}

