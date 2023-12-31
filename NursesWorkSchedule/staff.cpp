#include "staff.h"

Staff::Staff(int personsCount, int day, int month, int year)
    : m_personsCount(personsCount)
    , m_day(day)
    , m_month(month)
    , m_year(year)
{
}

Staff::~Staff()
{
}

int Staff::getPersonsCount() const
{
    return m_personsCount;
}

int Staff::getDay() const
{
    return m_day;
}

int Staff::getMonth() const
{
    return m_month;
}

int Staff::getYear() const
{
    return m_year;
}

void Staff::setPersonsCount(int personsCount)
{
    m_personsCount = personsCount;
}

void Staff::setDay(int day)
{
    m_day = day;
}

void Staff::setMonth(int month)
{
    m_month = month;
}

void Staff::setYear(int year)
{
    m_year = year;
}
