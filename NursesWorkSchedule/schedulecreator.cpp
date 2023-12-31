#include "schedulecreator.h"

scheduleCreator::scheduleCreator()
{
}

scheduleCreator::~scheduleCreator()
{
}

void scheduleCreator::readNurses(string CSVNursesFile)
{
    m_nurses = m_nursesParser.parseNurses(m_reader.readFile(CSVNursesFile));
}

void scheduleCreator::readHolidays(string CSVHolidaysFile)
{
    m_holidays = m_holidaysParser.parseHolidays(m_reader.readFile(CSVHolidaysFile));
}

void scheduleCreator::readStaff(string CSVHolidaysFile)
{
    m_staffs = m_staffParser.parseStaff(m_reader.readFile(CSVHolidaysFile));
}

void scheduleCreator::getDate()
{
    dateContainer.setDate();
}


void scheduleCreator::generatePlan()
{
    getDate();
    const int CURRENT_MONTH = dateContainer.getMonth();
    const int PLAN_MONTH = CURRENT_MONTH == 12 ? 1 : CURRENT_MONTH + 1;
    const int PLAN_YEAR = (dateContainer.getYear() + (PLAN_MONTH == 1 ? 1 : 0));
    const int PLAN_DAYS = PLAN_MONTH == 2 && isYearLeap(PLAN_YEAR) ? 29 : DAYS_OF_MONTH[PLAN_MONTH];
    while (true) {

    }

}

bool scheduleCreator::isYearLeap(int year) const
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int scheduleCreator::dayOfPlan(int day, int month, int year) const
{
    const int CURRENT_MONTH = dateContainer.getMonth();
    const int CURRENT_YEAR = dateContainer.getYear();
    if (CURRENT_MONTH == 12 && year == CURRENT_YEAR + 1 && month == 1) {
        return day;
    }
    if (month == CURRENT_MONTH + 1 && year == CURRENT_YEAR) {
        return day;
    }
    return -1;
}
