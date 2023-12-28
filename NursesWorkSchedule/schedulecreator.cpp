#include "schedulecreator.h"

scheduleCreator::scheduleCreator()
{
}

scheduleCreator::~scheduleCreator()
{
}

void scheduleCreator::generatePlan(string CSVNursesFile, string CSVHolidaysFile)
{
    m_nurses = m_nursesParser.parseNurses(m_reader.readFile(CSVNursesFile));
    m_holidays = m_holidaysParser.parseHolidays(m_reader.readFile(CSVNursesFile));
}
