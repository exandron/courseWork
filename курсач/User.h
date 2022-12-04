#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class User {
private:
    string login;
    string password;
    bool isAdmin;
    User* users;
    int usersAmount;

    void deleteUser(string filepath);
    void editUser(string filepath);
    void printUsers();
    void registerUser(string filename);
    void getUsersFromFile(string filename);
    void printUsersIntoFile(string filename);
    string inputPassword();
    int getAdminsAmount();
public:
    User();
    User(string login, string password, bool isAdmin, User* users, int usersAmount);
    string getLogin();
    string getPassword();
    bool getIsAdmin();
    User* getUsers();
    int getUsersAmount();
    void setLogin(string login);
    void setPassword(string password);
    void setIsAdmin(bool isAdmin);
    bool loginIntoSystem(string filename);
    void menu(string filepath);
    friend istream& operator >> (istream& in, User& user);
};