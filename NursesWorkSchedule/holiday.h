#pragma once

#include <string>

using namespace std;

class Holiday
{
public:
    Holiday(string firstname, string lastname, int day, int month, int year);
    ~Holiday();

    string getFirstname() const;
    string getLastname() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setFirstname(string firstname);
    void setLastname(string lastname);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

private:
    string m_firstname;
    string m_lastname;
    int m_day;
    int m_month;
    int m_year;
};

