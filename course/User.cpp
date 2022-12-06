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
}

User::User(string login, string password, bool isAdmin) {
    this->login = login;
    this->password = password;
    this->isAdmin = isAdmin;
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
        int size = this->users.size();
        vector<string> logins;
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
                        logins.push_back(token);
                    }
                    line.erase(0, pos + delimiter.length());
                }
            }
        }
        else {
            cout << "���� �� ������ !" << endl;
        }
        file.close();

        cout << "������� �����: ";
        string login;
        cin >> login;
        for (int i = 0; i < size; i++) {
            if (strcmp(login.c_str(), logins[i].c_str()) == 0) {
                cout << "������ ����� ��� �����!";
                return;
            }
        }
        cout << "������� ������: ";
        string password = inputPassword();
        cout << "������� �� ������� ������� ������������ ���������������?\n1 - ��\n0 - ���\n";
        int choice;
        while (true) {
            cin >> choice;
            if (choice == 1 || choice == 0) {
                break;
            }
            else {
                cout << "������� ������������ ��������! ��������� �������: ";
            }
        }
        ofstream file1;
        file1.open(filename, ios::app);
        if (file1.is_open()) {
            file1 << endl << login << ";" << password << ";" << choice << ";";
        }
        else {
            cout << "���� �� ������ !" << endl;
        }
        file1.close();
        getUsersFromFile(filename);
    }
    else {
        cout << "� ��� ��� �������!\n";
        return;
    }
}

bool User::loginIntoSystem(string filename) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        if (file.peek() == EOF) {
            cout << "�� ���������� ������� �������! ��������� ���������������� ������� ��������������!\n������� �����: ";
            string loginInput;
            cin >> loginInput;
            cout << "������� ������: ";
            string password = inputPassword();
            cout << "������������� ������� ���������������!\n";
            this->login = loginInput;
            this->password = password;
            this->isAdmin = true;
        }
        else {
            bool flag = false;
            for (int i = 0; true; i++) {
                string line;
                string loginInput;
                cout << "������� �����: ";
                cin >> loginInput;
                string loginTest = loginInput + ";";
                while (!file.eof()) {
                    getline(file, line);
                    if (line.find(loginTest) == 0) {
                        this->login = loginInput;
                        for (int j = 0; true; j++) {
                            cout << "������� ������: ";
                            size_t pos = 0;
                            string delimiter = ";";
                            string password = inputPassword();
                            string lineTmp = line;
                            for (int k = 0; (pos = lineTmp.find(delimiter)) != string::npos; k++) {
                                string token = lineTmp.substr(0, pos);
                                if (k == 1 && strcmp(password.c_str(), token.c_str()) != 0) {
                                    if (j != 2) {
                                        cout << "\n�������� ������! ��������� �������!" << endl;
                                        break;
                                    }
                                    else {
                                        cout << "\n�������� ������!";
                                        return false;
                                    }
                                }
                                if (k == 2) {
                                    this->password = password;
                                    isAdmin = stoi(token);
                                    getUsersFromFile(filename);
                                    cout << "\n����������� ������� ���������!" << endl;
                                    return true;
                                }
                                lineTmp.erase(0, pos + delimiter.length());
                            }
                        }
                    }
                }
                if (!flag) {
                    if (i < 2) {
                        cout << "\n�������� �����! ��������� �������!" << endl;
                        file.close();
                        file.open(filename);
                        continue;
                    }
                    else {
                        cout << "\n�������� �����!" << endl;
                        return false;
                    }
                }
            }
        }
    }
    else {
        cout << "���� �� ������ !" << endl;
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
        cout << "���� �� ������ !" << endl;
        return false;
    }
}

void User::menu(string filepath) {
    string filesname = "students.txt";
    Students students;
    students.readStudentsFromFile(filesname);
    if (isAdmin) {
        int choice;
        while (true) {
            cout << endl;
            cout << "   ���� ��������������   " << endl;
            cout << " 1 -  ���������� ��������" << endl;
            cout << " 2 -  �������� ���� ���������" << endl;
            cout << " 3 -  �������������� ��������" << endl;
            cout << " 4 -  �������� ��������" << endl;
            cout << " 5 -  ���������� ���������" << endl;
            cout << " 6 -  ����� ���������" << endl;
            cout << " 7 -  ������ ���������" << endl;
            cout << " 8 -  ������ ��������� ���������-�����������" << endl;
            cout << " 9 -  ����������� ������������" << endl;
            cout << " 10 - �������� �������������" << endl;
            cout << " 11 - �������������� ������������" << endl;
            cout << " 12 - �������� ������������" << endl;
            cout << " 0 -  �����" << endl;
            cout << endl;
            cout << "��� �����: ";
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
                students.filterStudents();
                break;
            case 8:
                students.getScholarshipStat();
                break;
            case 9:
                registerUser(filepath);
                break;
            case 10:
                printUsers();
                break;
            case 11:
                editUser(filepath);
                break;
            case 12:
                deleteUser(filepath);
                break;
            case 0:
                students.writeStudentsIntoFile(filesname);
                return;
            default:
                cout << "�������� ����!" << endl;
                break;
            }
        }
    }
    else {
        int choice;
        while (true) {
            cout << endl;
            cout << "   ���� ������������   " << endl;
            cout << " 1 - �������� ���� ���������" << endl;
            cout << " 2 - ���������� ���������" << endl;
            cout << " 3 - ����� ���������" << endl;
            cout << " 4 - ������ ��������� ���������-�����������" << endl;
            cout << " 0 - �����" << endl;
            cout << endl;
            cout << "��� �����: ";
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
                cout << "�������� ����!" << endl;
                break;
            }
        }
    }
}

void User::deleteUser(string filepath) {
    printUsers();
    cout << "������� ����� ������, ������� ������ �������: ";
    int choice;
    while (true) {
        cin >> choice;
        if (choice > this->users.size() || choice < 1) {
            cout << "��� ������ ��������! ��������� �������: ";
        }
        else if (getAdminsAmount() == 1 && users[choice - 1]->getIsAdmin()) {
            cout << "�� �� ������ ������� ������������� ��������������! ��������� �������: ";
        }
        else {
            cout << "������ ������� ������ ������� �������!" << endl;
            break;
        }
    }
    bool exitFlag = false;
    if (users[choice - 1]->getLogin() == login) {
        exitFlag = true;
    }
    users.erase(users.begin() + choice - 1);
    printUsersIntoFile(filepath);
    if (exitFlag) {
        exit(0);
    }
}

void User::editUser(string filepath) {
    printUsers();
    cout << "������� ����� ������, ������� ������ ��������: ";
    int choice;
    while (true) {
        cin >> choice;
        if (choice > this->users.size() || choice < 1) {
            cout << "��� ������ ��������! ��������� �������: ";
        }
        else {
            break;
        }
    }
    vector<string> logins;
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
                    logins.push_back(token);
                }
                line.erase(0, pos + delimiter.length());
            }
        }
    }
    else {
        cout << "���� �� ������ !" << endl;
    }
    file.close();
    int newChoice;
    cout << "1 - �����\n2 - ������\n3 - ����\n������� ����, ������� ������ ��������: ";
    cin >> newChoice;
    string login;
    string password;
    switch (newChoice) {
    case 1:
        cout << "������� �����: ";
        cin >> login;
        for (int i = 0; i < this->users.size(); i++) {
            if (strcmp(login.c_str(), logins[i].c_str()) == 0) {
                cout << "������ ����� ��� �����!";
                return;
            }
        }
        users[choice - 1]->setLogin(login);
        break;
    case 2:
        cout << "������� ������: ";
        password = inputPassword();
        users[choice - 1]->setPassword(password);
        break;
    case 3:
        cout << "������� �� ������� ������� ������������ ���������������?\n1 - ��\n0 - ���\n";
        int role;
        while (true) {
            cin >> role;
            if (role == 1 || role == 0) {
                cout << "������ ������� ������ ������� ���������������!" << endl;
                break;
            }
            else {
                cout << "������� ������������ ��������! ��������� �������: ";
            }
        }
        users[choice - 1]->setIsAdmin(role);
        break;
    default:
        break;
    }
    printUsersIntoFile(filepath);
}

void User::getUsersFromFile(string filename) {
    ifstream file;
    file.open(filename);
    int size = Students::getSizeFromFile(filename);
    users.clear();
    if (file.is_open()) {
        User user;
        for (int i = 0; i < size; i++) {
            file >> user;
            users.push_back(make_unique<User>(user.getLogin(), user.getPassword(), user.getIsAdmin()));
        }
    }
    else {
        cout << "���� �� ������ !" << endl;
    }
    file.close();
}

void User::printUsers() {
    cout << "+---+---------------------+--------------------+" << endl;
    cout << "| � |        �����        |        ����        |" << endl;
    cout << "+---+---------------------+--------------------+" << endl;
    for (int i = 0; i < this->users.size(); i++) {
        string role = users[i]->getIsAdmin() ? "�������������" : "������������";
        cout << left << "| " << setw(2) << i + 1 << "|  " << setw(19) << users[i]->getLogin() << "|  " << setw(18) << role << "|" << endl;
    }
    cout << "+---+---------------------+--------------------+" << endl;
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
        for (int i = 0; i < this->users.size(); i++) {
            file1 << users[i]->getLogin() << ";" << users[i]->getPassword() << ";" << users[i]->getIsAdmin() << ";";
            if (i != this->users.size() - 1) {
                file1 << endl;
            }
        }
    }
    else {
        cout << "���� �� ������ !" << endl;
    }
    file1.close();
}

int User::getAdminsAmount() {
    int result = 0;
    for (int i = 0; i < this->users.size(); i++) {
        if (users[i]->getIsAdmin()) {
            result++;
        }
    }
    return result;
}

vector<shared_ptr<User>> User::getUsers() {
    return users;
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