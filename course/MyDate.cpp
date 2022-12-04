#define _CRT_SECURE_NO_WARNINGS
#include "MyDate.h"
#include <time.h>

MyDate::MyDate() {
    day = 1;
    month = 1;
    year = 1;
}

MyDate::MyDate(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

MyDate::MyDate(const MyDate& date) {
    day = date.day;
    month = date.month;
    year = date.year;
}

MyDate::~MyDate() {}

int MyDate::getDay() {
    return day;
}

int MyDate::getMonth() {
    return month;
}

int MyDate::getYear() {
    return year;
}

void MyDate::setDay(int day) {
    this->day = day;
}

void MyDate::setMonth(int month) {
    this->month = month;
}

void MyDate::setYear(int year) {
    this->year = year;
}