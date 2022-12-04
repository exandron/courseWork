#pragma once
class MyDate {

    int day;
    int month;
    int year;
public:
    MyDate();
    MyDate(int day, int month, int year);
    MyDate(const MyDate& date);
    ~MyDate();
    int getDay();
    int getMonth();
    int getYear();
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    /*static bool isDate(string date) {
        size_t pos = 0;
        string delimiter = "/";
        date += delimiter;
        for (int j = 0; (pos = date.find(delimiter)) != string::npos; j++) {
            string token = date.substr(0, pos);
            if (!isNumeric(token))
                return false;
            switch (j) {
            case 0:
                if ((stoi(token) <= 0 || stoi(token) >= 31) && !Students::isSymbolic(stoi(token)))
                    return false;
                break;
            case 1:
                if ((stoi(token) <= 0 || stoi(token) >= 12) && !Students::isSymbolic(stoi(token)))
                    return false;
                break;
            case 2:
                if ((stoi(token) <= 0) && !Students::isSymbolic(stoi(token)))
                    return false;
                break;
            default: return false;
            }
            date.erase(0, pos + delimiter.length());
        }
        return true;
    };
    static bool isNumeric(string line) {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] < '0' || line[i]>'9')
                return false;
        }
        return true;
    }*/
};
