#include "holiday.h"

Holiday::Holiday(string firstname, string lastname, int day, int month, int year)
    : m_firstname(firstname)
    , m_lastname(lastname)
    , m_day(day)
    , m_month(month)
    , m_year(year)
{
}

Holiday::~Holiday()
{
}

string Holiday::getFirstname() const
{
    return m_firstname;
}

string Holiday::getLastname() const
{
    return m_lastname;
}

int Holiday::getDay() const
{
    return m_day;
}

int Holiday::getMonth() const
{
    return m_month;
}

int Holiday::getYear() const
{
    return m_year;
}

void Holiday::setFirstname(string firstname)
{
    m_firstname = firstname;
}

void Holiday::setLastname(string lastname)
{
    m_lastname = lastname;
}

void Holiday::setDay(int day)
{
    m_day = day;
}

void Holiday::setMonth(int month)
{
    m_month = month;
}

void Holiday::setYear(int year)
{
    m_year = year;
}
