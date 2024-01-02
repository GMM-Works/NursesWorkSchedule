#include "schedulecreator.h"

#include <cmath>

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

void scheduleCreator::generatePlan()
{
    getDate();
    const auto CURRENT_MONTH{dateContainer.getMonth()};
    const auto CURRENT_DAY_OF_WEEK{dateContainer.getDayOfWeek()};
    const auto CURRENT_DAY{dateContainer.getDay()};
    int planMonth;
    int planYear;
    if (CURRENT_MONTH == 12) {
        planMonth = 1;
        planYear = dateContainer.getYear() + 1;
    } else {
        planMonth = CURRENT_MONTH + 1;
        planYear = dateContainer.getYear();
    }
    const auto DAYS_OF_CURRENT_MONTH{CURRENT_MONTH == 2 && isYearLeap(planYear) ? 29 : DAYS_OF_MONTH[planMonth - 1]};
    m_startDayOfWeek = ((DAYS_OF_CURRENT_MONTH - CURRENT_DAY + CURRENT_DAY_OF_WEEK) % DAYS_OF_WEEK) + 1;
    const auto PLAN_DAYS{planMonth == 2 && isYearLeap(planYear) ? 29 : DAYS_OF_MONTH[planMonth - 1]};
    shifts = make_unique<Shift[]>(PLAN_DAYS);
    const auto FIRST_SUNDAY{8 - m_startDayOfWeek};
    const auto DAYS_AFTER_FIRST_WEEKEND = (PLAN_DAYS - FIRST_SUNDAY);
    const auto WEEKENDS_COUNT{DAYS_AFTER_FIRST_WEEKEND / DAYS_OF_WEEK + (DAYS_AFTER_FIRST_WEEKEND / DAYS_OF_WEEK == 6 ? 2 : 1)};
    const vector<Holiday> BASE_DAY_SHIFT_HOLIDAYS(m_holidays);
    const vector<Holiday> BASE_NIGHT_SHIFT_HOLIDAYS(m_holidays);
    for (auto iterator{0}; iterator < pow(WEEKENDS_COUNT, m_nurses.size()); iterator++) {
        vector<Holiday> dayShiftHolidays(BASE_DAY_SHIFT_HOLIDAYS);
        vector<Holiday> nightShiftHolidays(BASE_NIGHT_SHIFT_HOLIDAYS);
        for (auto iterator{1}; iterator <= m_nurses.size(); iterator++) {
            const auto WEEKEND_OFF{iterator % (int)pow(WEEKENDS_COUNT, iterator) / (int)pow(WEEKENDS_COUNT, iterator - 1)};

        };
    }
}

void scheduleCreator::getDate()
{
    dateContainer.setDate();
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
