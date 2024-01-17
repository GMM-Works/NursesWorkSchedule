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
    vector<vector<int>> indexesOfWorkedShifts;
    for (int i = 0; i < nurses.size(); ++i) {
        indexesOfWorkedShifts.push_back(vector<int>());
        for (int j = 0; j < dayShifts.size(); ++j) {
            if(j % 2 == 0){
                vector<Nurse> NursesAtDay = dayShifts[j].getNurses();
                for (int x = 0; x < NursesAtDay.size() ; ++x) {
                    if(nurses[i].getFirstname() == NursesAtDay[x].getFirstname() && nurses[i].getLastname() == NursesAtDay[x].getLastname()){
                        indexesOfWorkedShifts[i].push_back(j);
                    }
                }
            }
            else{
                vector<Nurse> NursesAtDay = nightShifts[j].getNurses();
                for (int x = 0; x < NursesAtDay.size() ; ++x) {
                    if(nurses[i].getFirstname() == NursesAtDay[x].getFirstname() && nurses[i].getLastname() == NursesAtDay[x].getLastname()){
                        indexesOfWorkedShifts[i].push_back(j);
                    }
                }
            }
        }
    }
    for (int i = 0; i <  indexesOfWorkedShifts.size(); ++i) {
        for (int j = 1; j < indexesOfWorkedShifts[i].size(); ++j) {
            EXPECT_NE(indexesOfWorkedShifts[i][j-1] +1 , indexesOfWorkedShifts[i][j]);
            EXPECT_NE(indexesOfWorkedShifts[i][j-1] +2 , indexesOfWorkedShifts[i][j]);
        }
        EXPECT_TRUE(indexesOfWorkedShifts[i].size() <= 13);
    }
}
