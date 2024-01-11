#include "schedulecreator.h"

#include <cmath>
#include <ctime>

#include <iostream>

ScheduleCreator::ScheduleCreator()
{
    srand( time( NULL ) );
}

ScheduleCreator::~ScheduleCreator()
{
}

void ScheduleCreator::readNurses(string CSVNursesFile)
{
    m_nurses = m_nursesParser.parseNurses(m_reader.readFile(CSVNursesFile));
}

void ScheduleCreator::readHolidays(string CSVHolidaysFile)
{
    m_holidays = m_holidaysParser.parseHolidays(m_reader.readFile(CSVHolidaysFile));
}

void ScheduleCreator::readStaff(string CSVHolidaysFile)
{
    m_staffs = m_staffParser.parseStaff(m_reader.readFile(CSVHolidaysFile));
}


void ScheduleCreator::generatePlan(string outputFileName)
{
    getDate();
    const auto currentMonth{m_dateContainer.getMonth()};
    const auto currentDayOfWeek{m_dateContainer.getDayOfWeek()};
    const auto currentDay{m_dateContainer.getDay()};
    int planMonth;
    int planYear;
    if (currentMonth == 12) {
        planMonth = 1;
        planYear = m_dateContainer.getYear() + 1;
    } else {
        planMonth = currentMonth + 1;
        planYear = m_dateContainer.getYear();
    }
    const auto daysOfCurrentMonth{currentMonth == 2 && isYearLeap(planYear) ? 29 : DAYS_OF_MONTH[planMonth - 1]};
    m_startDayOfWeek = ((daysOfCurrentMonth - currentDay + currentDayOfWeek) % DAYS_OF_WEEK) + 1;
    const auto planDays{planMonth == 2 && isYearLeap(planYear) ? 29 : DAYS_OF_MONTH[planMonth - 1]};
    const auto firstSunday{8 - m_startDayOfWeek};
    const auto daysAfterFirstWeekend = (planDays - firstSunday);
    const auto weekendsCount{daysAfterFirstWeekend / DAYS_OF_WEEK + (daysAfterFirstWeekend / DAYS_OF_WEEK == 6 ? 2 : 1)};
    const vector<Holiday> baseDayShiftHolidays(m_holidays);
    const vector<Holiday> baseNightShiftHolidays(m_holidays);
    const auto availableNurses{m_nurses.size()};
    while (true) {
        vector<Shift> dayShifts(planDays);
        vector<Shift> nightShifts(planDays);
        vector<vector<bool>> dayAfterHours(planDays);
        vector<vector<bool>> nightAfterHours(planDays);

        for (auto iterator{0}; iterator < planDays; iterator++) {
            auto personsForDay{0};
            for (auto &staff : m_staffs)
            {
                if (staff.getDay() == (iterator + 1) && staff.getMonth() == planMonth && staff.getYear() == planYear ) {
                    personsForDay = staff.getPersonsCount();
                }
            }
            if (!personsForDay) {
                personsForDay = DEFAULT_PERSONS_FOR_SHIFT;
            }

            dayAfterHours[iterator].resize(personsForDay);
            nightAfterHours[iterator].resize(personsForDay);

            for (auto personIndex{0}; personIndex < personsForDay; personIndex++) {
                dayShifts[iterator].addNurse(m_nurses[rand() % availableNurses]);
                dayAfterHours[iterator][personIndex] = rand() % 2;
            }

            for (auto personIndex{0}; personIndex < personsForDay; personIndex++) {
                nightShifts[iterator].addNurse(m_nurses[rand() % availableNurses]);;
                nightAfterHours[iterator][personIndex] = rand() % 2;
            }

        }

        bool threeShiftsInWeek{true};
        bool twelveHoursBreak{true};
        bool oneFreeWeekend{true};
        bool oneOrLessAfterHours{true};

        //checking for threeShiftsInWeek


        vector<int> shiftsCount(m_nurses.size(), 0);
        for (auto iterator{0}; iterator < m_nurses.size(); iterator++) {
            for (auto iterator1{0}; iterator1 < planDays; iterator1++) {
                auto nursesOfDay =  dayShifts[iterator1].getNurses();
                auto nursesOfNight = nightShifts[iterator1].getNurses();
                for (auto iterator2{0}; iterator2 < nursesOfDay.size(); iterator2++) {
                    if (nursesOfDay[iterator2].getFirstname() ==  m_nurses[iterator].getFirstname() && nursesOfDay[iterator2].getLastname() ==  m_nurses[iterator].getLastname() && dayAfterHours[iterator1][iterator2] == false ) {
                        shiftsCount[iterator]++;
                    }
                }

                for (auto iterator2{0}; iterator2 < nursesOfNight.size(); iterator2++) {
                    if (nursesOfNight[iterator2].getFirstname() ==  m_nurses[iterator].getFirstname() && nursesOfNight[iterator2].getLastname() ==  m_nurses[iterator].getLastname() && nightAfterHours[iterator1][iterator2] == false ) {
                        shiftsCount[iterator]++;
                    }
                }
            }
        }

        for (auto &nurse : shiftsCount) {
            if (nurse != 3 && nurse != 0) {
                threeShiftsInWeek = false;
            }
        }


        if (threeShiftsInWeek && twelveHoursBreak && oneFreeWeekend && oneOrLessAfterHours) {
            m_dayShifts = dayShifts;
            m_nightShifts = nightShifts;
            break;
        }
    }

    m_writer.open(outputFileName);

    for (auto iterator{0}; iterator < planDays; iterator++) {
        vector<Nurse> dayNurses = m_dayShifts[iterator].getNurses();
        vector<Nurse> nightNurses = m_nightShifts[iterator].getNurses();
        m_writer.writeLine(to_string(iterator + 1) + "." + to_string(planMonth) + "." + to_string(planYear) + ";");
        m_writer.writeLine("zmiana dzienna:;");
        string dayOutput;
        for (auto nursesIndex{0};  nursesIndex < dayNurses.size(); nursesIndex++) {
            dayOutput += dayNurses[nursesIndex].getFirstname() + " " + dayNurses[nursesIndex].getLastname() + ";";
        }
        m_writer.writeLine(dayOutput);
        m_writer.writeLine("zmiana nocna:;");
        string nightOutput;
        for (auto nursesIndex{0};  nursesIndex < nightNurses.size(); nursesIndex++) {
            nightOutput += nightNurses[nursesIndex].getFirstname() + " " + nightNurses[nursesIndex].getLastname() + ";";
        }
        m_writer.writeLine(nightOutput);
    }

}

void ScheduleCreator::getDate()
{
    m_dateContainer.setDate();
}

bool ScheduleCreator::isYearLeap(int year) const
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int ScheduleCreator::dayOfPlan(int day, int month, int year) const
{
    const int currentMonth = m_dateContainer.getMonth();
    const int CURRENT_YEAR = m_dateContainer.getYear();
    if (currentMonth == 12 && year == CURRENT_YEAR + 1 && month == 1) {
        return day;
    }
    if (month == currentMonth + 1 && year == CURRENT_YEAR) {
        return day;
    }
    return -1;
}
