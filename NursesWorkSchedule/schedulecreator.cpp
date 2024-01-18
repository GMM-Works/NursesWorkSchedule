#include "schedulecreator.h"

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
    const auto firstSunday{6 - m_startDayOfWeek};
    const auto daysAfterFirstWeekend = (planDays - firstSunday);
    const auto weekendsCount{daysAfterFirstWeekend / DAYS_OF_WEEK + (daysAfterFirstWeekend / DAYS_OF_WEEK == 6 ? 2 : 1)};
    const vector<Holiday> baseDayShiftHolidays(m_holidays);
    const vector<Holiday> baseNightShiftHolidays(m_holidays);

    while (true) {
        bool twelveHoursBreak{true};
        bool oneFreeWeekend{true};
        bool oneOrLessAfterHours{true};
        bool compatibleWithHolidays{true};

        vector<Shift> currentDayShifts(planDays);
        vector<Shift> currentNightShifts(planDays);
        vector<vector<bool>> currentDayAfterHours(planDays);
        vector<vector<bool>> currentNightAfterHours(planDays);

        for (auto iterator{0}; iterator < planDays; ++iterator) {
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

            currentDayAfterHours[iterator].resize(personsForDay);

            currentNightAfterHours[iterator].resize(personsForDay);
        }

        vector<Nurse> availableNurses = m_nurses;
        auto success{false};
        while (true) {
            success = generatePlanPart(currentDayShifts, currentNightShifts, currentDayAfterHours, currentNightAfterHours, 0, firstSunday);
            if (!success) {
                continue;
            }
            auto daysCompleted{firstSunday};
            while (daysCompleted < planDays - 7) {
                auto success{false};
                success = generatePlanPart(currentDayShifts, currentNightShifts, currentDayAfterHours, currentNightAfterHours, daysCompleted, daysCompleted + 7);
                if (!success) {
                    continue;
                }
                daysCompleted += 7;
            }
            success = generatePlanPart(currentDayShifts, currentNightShifts, currentDayAfterHours, currentNightAfterHours, daysCompleted, planDays);
            if (!success) {
                continue;
            }
            break;
        }

        oneFreeWeekend = validateForWeekends(currentDayShifts, currentNightShifts, firstSunday, planDays);

        compatibleWithHolidays = validateForHolidays(currentDayShifts, currentNightShifts, planMonth, planYear);

        if (twelveHoursBreak && oneFreeWeekend && oneOrLessAfterHours && compatibleWithHolidays) {
            m_dayShifts = currentDayShifts;
            m_nightShifts = currentNightShifts;
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

bool ScheduleCreator::generatePlanPart(vector<Shift> &dayShifts, vector<Shift> &nightShifts, vector<vector<bool> > &dayAfterHours, vector<vector<bool>> &nightAfterHours, int startDay, int endDay)
{
    auto resets{0};
    vector<Nurse> availableNurses = m_nurses;
    for (auto iterator{startDay}; iterator < endDay; ++iterator) {
        dayShifts[iterator].getNurses().clear();
        nightShifts[iterator].getNurses().clear();
    }

    while (true) {
        vector<Shift> cloneDayShifts = dayShifts;
        vector<Shift> cloneNightShifts = nightShifts;
        vector<vector<bool>> cloneDayAfterHours{dayAfterHours};
        vector<vector<bool>> cloneNightAfterHours{nightAfterHours};

        for (auto iterator{startDay}; iterator < endDay; ++iterator) {

            auto currentNurses{availableNurses};
            for (auto setNurse{0}; setNurse < dayShifts[iterator].getNurses().size(); ++setNurse) {
                for (auto allNurses{0}; allNurses < currentNurses.size(); ++allNurses) {
                    if (dayShifts[iterator].getNurses()[setNurse] == currentNurses[allNurses]) {
                        currentNurses.erase(currentNurses.begin() + allNurses);
                        break;
                    }
                }
            }

            for (auto personIndex{dayShifts[iterator].getNurses().size()}; personIndex < cloneDayAfterHours[iterator].size(); ++personIndex) {
                auto chosenIndex{rand() % currentNurses.size()};
                cloneDayShifts[iterator].addNurse(currentNurses[chosenIndex]);
                currentNurses.erase(currentNurses.begin() + chosenIndex);
                cloneDayAfterHours[iterator][personIndex] = rand() % 2;
            }

            currentNurses = availableNurses;
            for (auto setNurse{0}; setNurse < nightShifts[iterator].getNurses().size(); ++setNurse) {
                for (auto allNurses{0}; allNurses < currentNurses.size(); ++allNurses) {
                    if (nightShifts[iterator].getNurses()[setNurse] == currentNurses[allNurses]) {
                        currentNurses.erase(currentNurses.begin() + allNurses);
                        break;
                    }
                }
            }

            for (auto personIndex{nightShifts[iterator].getNurses().size()}; personIndex < cloneNightAfterHours[iterator].size(); ++personIndex) {
                auto chosenIndex{rand() % currentNurses.size()};
                cloneNightShifts[iterator].addNurse(currentNurses[chosenIndex]);
                currentNurses.erase(currentNurses.begin() + chosenIndex);
                cloneNightAfterHours[iterator][personIndex] = rand() % 2;
            }

        }

        //checking for threeShiftsInWeek

        vector<int> shiftsCount(availableNurses.size(), 0);
        for (auto iterator{0}; iterator < availableNurses.size(); ++iterator) {
            for (auto iterator1{startDay}; iterator1 < endDay; ++iterator1) {
                auto nursesOfDay =  cloneDayShifts[iterator1].getNurses();
                auto nursesOfNight = cloneNightShifts[iterator1].getNurses();
                for (auto iterator2{dayShifts[iterator1].getNurses().size()}; iterator2 < nursesOfDay.size(); ++iterator2) {
                    if (nursesOfDay[iterator2] ==  availableNurses[iterator] && cloneDayAfterHours[iterator1][iterator2] == false ) {
                        shiftsCount[iterator]++;
                    }
                }

                for (auto iterator2{nightShifts[iterator1].getNurses().size()}; iterator2 < nursesOfNight.size(); ++iterator2) {
                    if (nursesOfNight[iterator2] ==  availableNurses[iterator] && cloneNightAfterHours[iterator1][iterator2] == false ) {
                        shiftsCount[iterator]++;
                    }
                }
            }
        }

        for (auto iterator{0}; iterator < shiftsCount.size(); ++iterator) {
            if (shiftsCount[iterator] == 3) {
                for (auto iterator1{startDay}; iterator1 < endDay; ++iterator1) {
                    auto nursesOfDay =  cloneDayShifts[iterator1].getNurses();
                    auto nursesOfNight = cloneNightShifts[iterator1].getNurses();
                    for (auto iterator2{0}; iterator2 < nursesOfDay.size(); ++iterator2) {
                        if (nursesOfDay[iterator2] == availableNurses[iterator] && cloneDayAfterHours[iterator1][iterator2] == false ) {
                            dayShifts[iterator1].addNurse(nursesOfDay[iterator2]);
                            dayAfterHours[iterator1][iterator2] = cloneDayAfterHours[iterator1][iterator2];
                        }
                    }

                    for (auto iterator2{0}; iterator2 < nursesOfNight.size(); ++iterator2) {
                        if (nursesOfNight[iterator2] == availableNurses[iterator] && cloneNightAfterHours[iterator1][iterator2] == false ) {
                            nightShifts[iterator1].addNurse(nursesOfNight[iterator2]);
                            nightAfterHours[iterator1][iterator2] = cloneNightAfterHours[iterator1][iterator2];
                        }
                    }
                }

                for (auto iterator1{iterator}; iterator1 < availableNurses.size() - 1; iterator1++) {
                    availableNurses[iterator1] = availableNurses[iterator1 + 1];
                }
                availableNurses.pop_back();

                for (auto iterator1{iterator}; iterator1 < shiftsCount.size() - 1; iterator1++) {
                    shiftsCount[iterator1] = shiftsCount[iterator1 + 1];
                }
                shiftsCount.pop_back();

                iterator = 0;
            }
        }

        auto allHours{0};
        auto reservedHours{0};

        for (auto iterator1{startDay}; iterator1 < endDay; ++iterator1) {
            allHours += dayAfterHours[iterator1].size() + nightAfterHours[iterator1].size();
            reservedHours += dayShifts[iterator1].getNurses().size() + nightShifts[iterator1].getNurses().size();            
        }

        if ((allHours - reservedHours) < 3 || availableNurses.size() == 1) {
            return true;
        } else {
            ++resets;
            if (resets == MAXIMAL_ROLL_RESTARTS) {
                return false;
            }
        }
    }
}

bool ScheduleCreator::validateForWeekends(vector<Shift> &dayShifts, vector<Shift> &nightShifts, int firstSunday, int planDays) const
{
    vector<Nurse> usedNurses;
    for (auto days{0}; days < dayShifts.size(); ++days) {
        auto thisDayNurses{dayShifts[days].getNurses()};
        auto thisNightNurses{nightShifts[days].getNurses()};
        for (auto day{0}; day < thisDayNurses.size(); ++day) {
            auto exitCode{true};
            for (auto &nurse : usedNurses) {
                if (nurse == thisDayNurses[day]) {
                    exitCode = false;
                }
            }
            if (exitCode) {
                usedNurses.push_back(thisDayNurses[day]);
            }
        }

        for (auto night{0}; night < thisNightNurses.size(); ++night) {
            auto exitCode{true};
            for (auto &nurse : usedNurses) {
                if (nurse == thisNightNurses[night]) {
                    exitCode = false;
                }
            }
            if (exitCode) {
                usedNurses.push_back(thisNightNurses[night]);
            }
        }
    }

    for (auto & nurse : usedNurses) {
        auto currentSunday{firstSunday};
        bool freeWeekend{false};
        while (currentSunday <= planDays - 1) {
            bool isWeekendFree{true};
            for (auto &person : dayShifts[currentSunday].getNurses()) {
                if (person == nurse) {
                    isWeekendFree = false;
                }
            }
            for (auto &person : dayShifts[currentSunday - 1].getNurses()) {
                if (person == nurse) {
                    isWeekendFree = false;
                }
            }
            for (auto &person : nightShifts[currentSunday].getNurses()) {
                if (person == nurse) {
                    isWeekendFree = false;
                }
            }
            for (auto &person : nightShifts[currentSunday - 1].getNurses()) {
                if (person == nurse) {
                    isWeekendFree = false;
                }
            }
            if (isWeekendFree) {
                freeWeekend = true;
                break;
            }
            currentSunday += 7;
        }

        if (!freeWeekend) {
            return false;
        }

    }
    return true;
}

bool ScheduleCreator::validateForHolidays(vector<Shift> &dayShifts, vector<Shift> &nightShifts, int planMonth, int planYear) const
{
    for (auto &holiday : m_holidays) {
        if (holiday.getMonth() == planMonth && holiday.getYear() == planYear) {
            for (auto day{0}; day < dayShifts.size(); ++day) {
                for (auto &person : dayShifts[day].getNurses()) {
                    if (person.getFirstname() == holiday.getFirstname() && person.getLastname() == person.getFirstname()) {
                        return false;
                    }
                }
                for (auto &person : nightShifts[day].getNurses()) {
                    if (person.getFirstname() == holiday.getFirstname() && person.getLastname() == person.getFirstname()) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

