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
    const auto firstSunday{6 - m_startDayOfWeek};
    const auto daysAfterFirstWeekend = (planDays - firstSunday);
    const auto weekendsCount{daysAfterFirstWeekend / DAYS_OF_WEEK + (daysAfterFirstWeekend / DAYS_OF_WEEK == 6 ? 2 : 1)};
    const vector<Holiday> baseDayShiftHolidays(m_holidays);
    const vector<Holiday> baseNightShiftHolidays(m_holidays);

    while (true) {
        bool twelveHoursBreak{true};
        bool oneFreeWeekend{true};
        bool oneOrLessAfterHours{true};

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

        generatePlanPart(currentDayShifts, currentNightShifts, currentDayAfterHours, currentNightAfterHours, 0, firstSunday);
        auto daysCompleted{firstSunday};
        while (daysCompleted < planDays - 7) {
            generatePlanPart(currentDayShifts, currentNightShifts, currentDayAfterHours, currentNightAfterHours, daysCompleted, daysCompleted + 7);
            daysCompleted += 7;
        }
        generatePlanPart(currentDayShifts, currentNightShifts, currentDayAfterHours, currentNightAfterHours, daysCompleted, planDays);

        // while (true) {
        //     vector<Shift> dayShifts = currentDayShifts;
        //     vector<Shift> nightShifts = currentNightShifts;
        //     vector<vector<bool>> dayAfterHours{currentDayAfterHours};
        //     vector<vector<bool>> nightAfterHours{currentNightAfterHours};
        //     const auto nursesCount{availableNurses.size()};

        //     for (auto iterator{0}; iterator < planDays; ++iterator) {
        //         for (auto personIndex{currentDayShifts[iterator].getNurses().size()}; personIndex < dayAfterHours[iterator].size(); ++personIndex) {
        //             dayShifts[iterator].addNurse(availableNurses[rand() % nursesCount]);
        //             dayAfterHours[iterator][personIndex] = rand() % 2;
        //         }

        //         for (auto personIndex{currentNightShifts[iterator].getNurses().size()}; personIndex < nightAfterHours[iterator].size(); ++personIndex) {
        //             nightShifts[iterator].addNurse(availableNurses[rand() % nursesCount]);
        //             nightAfterHours[iterator][personIndex] = rand() % 2;
        //         }

        //     }

        //     //checking for threeShiftsInWeek


        //     vector<int> shiftsCount(availableNurses.size(), 0);
        //     for (auto iterator{0}; iterator < availableNurses.size(); ++iterator) {
        //         for (auto iterator1{0}; iterator1 < planDays; ++iterator1) {
        //             auto nursesOfDay =  dayShifts[iterator1].getNurses();
        //             auto nursesOfNight = nightShifts[iterator1].getNurses();
        //             for (auto iterator2{currentDayShifts[iterator1].getNurses().size()}; iterator2 < nursesOfDay.size(); ++iterator2) {
        //                 if (nursesOfDay[iterator2].getFirstname() ==  availableNurses[iterator].getFirstname() && nursesOfDay[iterator2].getLastname() ==  availableNurses[iterator].getLastname() && dayAfterHours[iterator1][iterator2] == false ) {
        //                     shiftsCount[iterator]++;
        //                 }
        //             }

        //             for (auto iterator2{currentNightShifts[iterator1].getNurses().size()}; iterator2 < nursesOfNight.size(); ++iterator2) {
        //                 if (nursesOfNight[iterator2].getFirstname() ==  availableNurses[iterator].getFirstname() && nursesOfNight[iterator2].getLastname() ==  availableNurses[iterator].getLastname() && nightAfterHours[iterator1][iterator2] == false ) {
        //                     shiftsCount[iterator]++;
        //                 }
        //             }
        //         }
        //     }

        //     for (auto iterator{0}; iterator < shiftsCount.size(); ++iterator) {
        //         if (shiftsCount[iterator] == 3) {
        //             for (auto iterator1{0}; iterator1 < planDays; ++iterator1) {
        //                 auto nursesOfDay =  dayShifts[iterator1].getNurses();
        //                 auto nursesOfNight = nightShifts[iterator1].getNurses();
        //                 for (auto iterator2{0}; iterator2 < nursesOfDay.size(); ++iterator2) {
        //                     if (nursesOfDay[iterator2].getFirstname() ==  availableNurses[iterator].getFirstname() && nursesOfDay[iterator2].getLastname() ==  availableNurses[iterator].getLastname() && dayAfterHours[iterator1][iterator2] == false ) {
        //                         currentDayShifts[iterator1].addNurse(nursesOfDay[iterator2]);
        //                         currentDayAfterHours[iterator1][iterator2] = dayAfterHours[iterator1][iterator2];
        //                     }
        //                 }

        //                 for (auto iterator2{0}; iterator2 < nursesOfNight.size(); ++iterator2) {
        //                     if (nursesOfNight[iterator2].getFirstname() ==  availableNurses[iterator].getFirstname() && nursesOfNight[iterator2].getLastname() ==  availableNurses[iterator].getLastname() && nightAfterHours[iterator1][iterator2] == false ) {
        //                         currentNightShifts[iterator1].addNurse(nursesOfNight[iterator2]);
        //                         currentNightAfterHours[iterator1][iterator2] = nightAfterHours[iterator1][iterator2];
        //                     }
        //                 }
        //             }

        //             for (auto iterator1{iterator}; iterator1 < availableNurses.size() - 1; iterator1++) {
        //                 availableNurses[iterator1] = availableNurses[iterator1 + 1];
        //             }
        //             availableNurses.pop_back();

        //             for (auto iterator1{iterator}; iterator1 < shiftsCount.size() - 1; iterator1++) {
        //                shiftsCount[iterator1] = shiftsCount[iterator1 + 1];
        //             }
        //             shiftsCount.pop_back();

        //             iterator = 0;
        //         }
        //     }

        //     auto allHours{0};
        //     auto reservedHours{0};

        //     for (auto iterator1{0}; iterator1 < planDays; ++iterator1) {
        //         allHours += currentDayAfterHours[iterator1].size() + currentNightAfterHours[iterator1].size();
        //         reservedHours += currentDayShifts[iterator1].getNurses().size() + currentNightShifts[iterator1].getNurses().size();
        //     }

        //     if ((allHours - reservedHours) < 3 || availableNurses.size() == 1) {
        //         break;
        //     }
        // }

        // if (twelveHoursBreak && oneFreeWeekend && oneOrLessAfterHours) {
        m_dayShifts = currentDayShifts;
        m_nightShifts = currentNightShifts;
        break;
        // }
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

void ScheduleCreator::generatePlanPart(vector<Shift> &dayShifts, vector<Shift> &nightShifts, vector<vector<bool> > &dayAfterHours, vector<vector<bool>> &nightAfterHours, int startDay, int endDay)
{
    vector<Nurse> availableNurses = m_nurses;
    while (true) {
        vector<Shift> cloneDayShifts = dayShifts;
        vector<Shift> cloneNightShifts = nightShifts;
        vector<vector<bool>> cloneDayAfterHours{dayAfterHours};
        vector<vector<bool>> cloneNightAfterHours{nightAfterHours};
        const auto nursesCount{availableNurses.size()};

        for (auto iterator{startDay}; iterator < endDay; ++iterator) {
            for (auto personIndex{dayShifts[iterator].getNurses().size()}; personIndex < cloneDayAfterHours[iterator].size(); ++personIndex) {
                cloneDayShifts[iterator].addNurse(availableNurses[rand() % nursesCount]);
                cloneDayAfterHours[iterator][personIndex] = rand() % 2;
            }

            for (auto personIndex{nightShifts[iterator].getNurses().size()}; personIndex < cloneNightAfterHours[iterator].size(); ++personIndex) {
                cloneNightShifts[iterator].addNurse(availableNurses[rand() % nursesCount]);
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
            break;
        }
    }
}
