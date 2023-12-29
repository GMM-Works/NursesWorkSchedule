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

void scheduleCreator::getDate()
{
    dateContainer.setDate();
}

void scheduleCreator::generatePlan()
{
    dateContainer.setDate();


}
