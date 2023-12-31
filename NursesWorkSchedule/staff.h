#pragma once

#include <string>

using namespace std;

class Staff
{
public:
    Staff(int day, int month, int year, int personsCount);
    ~Staff();

    int getPersonsCount() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setPersonsCount(int personsCount);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

private:
    int m_personsCount;
    int m_day;
    int m_month;
    int m_year;
};
