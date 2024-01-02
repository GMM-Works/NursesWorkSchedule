#include "currentdate.h"
#include <ctime>

CurrentDate::CurrentDate()
{
}

CurrentDate::~CurrentDate()
{
}

void CurrentDate::setDate()
{
    time_t t = std::time(0);
    struct tm *currentTime = localtime(&t);
    m_day = currentTime->tm_mday;
    m_month = currentTime->tm_mon + 1;
    m_year = currentTime->tm_year + 1900;
    m_dayOfWeek = currentTime->tm_wday + 1;
}

int CurrentDate::getDay() const
{
    return m_day;
}

int CurrentDate::getMonth() const
{
    return m_month;
}

int CurrentDate::getYear() const
{
    return m_year;
}

int CurrentDate::getDayOfWeek() const
{
    return m_dayOfWeek;
}
