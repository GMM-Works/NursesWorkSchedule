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
    struct tm *aTime = localtime(&t);
    m_day = aTime->tm_mday;
    m_month = aTime->tm_mon + 1;
    m_year = aTime->tm_year + 1900;
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
