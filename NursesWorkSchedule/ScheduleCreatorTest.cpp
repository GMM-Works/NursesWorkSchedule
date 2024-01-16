#include <gtest/gtest.h>
#include "schedulecreator.h"
#include <string>
#include <vector>

class ScheduleCreatorFixtureTests : public ::testing::Test
{
protected:
    ScheduleCreator scheduleCreator;
};

TEST_F(ScheduleCreatorFixtureTests , TestOfWorkedShifts){

    scheduleCreator.readHolidays("../NursesWorkSchedule/holidays.csv");
    scheduleCreator.readStaff("../NursesWorkSchedule/staff.csv");
    scheduleCreator.readNurses("../NursesWorkSchedule/nurses.csv");
    scheduleCreator.generatePlan("workScheduleTest.csv");
    vector<Holiday> holidays = scheduleCreator.getHolidays();
    vector<Staff> staff = scheduleCreator.getStaff();
    vector<Nurse> nurses = scheduleCreator.getNurses();
    vector<Shift> dayShifts = scheduleCreator.getDayShifts();
    vector<Shift> nightShifts = scheduleCreator.getNightShifts();
    vector<int> WorkedShifts;
    for (int i = 0; i < nurses.size(); ++i) {
        WorkedShifts.push_back(0);
        for (int j = 0; j < dayShifts.size(); ++j) {
            vector<Nurse> NursesAtDay = dayShifts[j].getNurses();
            for (int x = 0; x < NursesAtDay.size() ; ++x) {
                if(nurses[i].getFirstname() == NursesAtDay[x].getFirstname() && nurses[i].getLastname() == NursesAtDay[x].getLastname()){
                    WorkedShifts[i] += 1;
                }
            }
        }
        for (int j = 0; j < nightShifts.size(); ++j) {
            vector<Nurse> NursesAtDay = nightShifts[j].getNurses();
            for (int x = 0; x < NursesAtDay.size() ; ++x) {
                if(nurses[i].getFirstname() == NursesAtDay[x].getFirstname() && nurses[i].getLastname() == NursesAtDay[x].getLastname()){
                    WorkedShifts[i] += 1;
                }
            }
        }
    }
    for (int i = 0; i < WorkedShifts.size(); ++i) {
        //int tmp = dayShifts.size()/5;
        EXPECT_TRUE(WorkedShifts[i] <= 13);
    }
}
