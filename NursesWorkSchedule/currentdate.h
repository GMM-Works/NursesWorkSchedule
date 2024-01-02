#pragma once

class CurrentDate
{
public:
    CurrentDate();
    ~CurrentDate();

    void setDate();
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getDayOfWeek() const;

private:
    int m_day;
    int m_month;
    int m_year;
    int m_dayOfWeek;

};
