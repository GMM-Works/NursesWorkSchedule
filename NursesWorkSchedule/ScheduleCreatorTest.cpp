#include <gtest/gtest.h>
#include "schedulecreator.h"
#include <string>
#include <vector>

class ScheduleCreatorFixtureTests : public ::testing::Test
{
protected:
    void generateSchedule () {
        m_scheduleCreator.readHolidays("../NursesWorkSchedule/holidays.csv");
        m_scheduleCreator.readStaff("../NursesWorkSchedule/staff.csv");
        m_scheduleCreator.readNurses("../NursesWorkSchedule/nurses.csv");
        m_scheduleCreator.generatePlan("workScheduleTest.csv");
        m_holidays = m_scheduleCreator.getHolidays();
        m_staff = m_scheduleCreator.getStaff();
        m_nurses = m_scheduleCreator.getNurses();
        m_dayShifts = m_scheduleCreator.getDayShifts();
        m_nightShifts = m_scheduleCreator.getNightShifts();
    }
protected:
    ScheduleCreator m_scheduleCreator;
    vector<Holiday> m_holidays;
    vector<Staff> m_staff;
    vector<Nurse> m_nurses;
    vector<Shift> m_dayShifts;
    vector<Shift> m_nightShifts;
};

TEST_F(ScheduleCreatorFixtureTests , TestBreaksBetweenShiftsAndWorkedHours){
    generateSchedule();
    vector<vector<int>> indexesOfWorkedShifts;
    for (auto i = 0; i < m_nurses.size(); ++i) {
        indexesOfWorkedShifts.push_back(vector<int>());
        for (auto j = 0; j < m_dayShifts.size(); ++j) {
            if(j % 2 == 0){
                vector<Nurse> NursesAtDay = m_dayShifts[j].getNurses();
                for (auto x = 0; x < NursesAtDay.size() ; ++x) {
                    if(m_nurses[i].getFirstname() == NursesAtDay[x].getFirstname() && m_nurses[i].getLastname() == NursesAtDay[x].getLastname()){
                        indexesOfWorkedShifts[i].push_back(j);
                    }
                }
            }
            else if(j % 2 != 0){
                vector<Nurse> NursesAtDay = m_nightShifts[j].getNurses();
                for (auto x = 0; x < NursesAtDay.size(); ++x) {
                    if(m_nurses[i].getFirstname() == NursesAtDay[x].getFirstname() && m_nurses[i].getLastname() == NursesAtDay[x].getLastname()){
                        indexesOfWorkedShifts[i].push_back(j);
                    }
                }
            }
        }
    }
    for (auto i = 0; i <  indexesOfWorkedShifts.size(); ++i) {
        for (auto j = 1; j < indexesOfWorkedShifts[i].size(); ++j) {
            EXPECT_NE(indexesOfWorkedShifts[i][j-1] +1 , indexesOfWorkedShifts[i][j]);
            EXPECT_NE(indexesOfWorkedShifts[i][j-1] +2 , indexesOfWorkedShifts[i][j]);
        }
        EXPECT_TRUE(indexesOfWorkedShifts[i].size() <= 13);
    }
}

TEST_F(ScheduleCreatorFixtureTests , TestNumberOfEmployeeOnShift){
    generateSchedule();
    for (auto j = 0; j < m_dayShifts.size(); ++j) {
        if(j % 2 == 0){
            vector<Nurse> NursesAtDay = m_dayShifts[j].getNurses();
            EXPECT_TRUE(NursesAtDay.size() >= 2);
        }
        else if(j % 2 != 0){
            vector<Nurse> NursesAtDay = m_nightShifts[j].getNurses();
            EXPECT_TRUE(NursesAtDay.size() >= 2);
            }
    }
}
