#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>

using namespace std;

class User {
private:
    string login;
    string password;
    bool isAdmin;
    vector<shared_ptr<User>> users;
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
    User(string login, string password, bool isAdmin);
    string getLogin();
    string getPassword();
    bool getIsAdmin();
    vector<shared_ptr<User>> getUsers();
    void setLogin(string login);
    void setPassword(string password);
    void setIsAdmin(bool isAdmin);
    bool loginIntoSystem(string filename);
    void menu(string filepath);
    friend istream& operator >> (istream& in, User& user);
};
