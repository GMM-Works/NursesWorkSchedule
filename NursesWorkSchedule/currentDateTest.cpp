#include <gtest/gtest.h>
#include "currentdate.h"
#include <ctime>

class CurrentDateFixtureTests : public ::testing::Test
{
    protected:
        CurrentDate currentDate = CurrentDate();
};

TEST_F (CurrentDateFixtureTests, CheckingEqualityOfCurentDate){
    currentDate.setDate();
    time_t actualDate = std::time(0);
    struct tm *TestedActualDate = localtime( &actualDate );
    int m_day = TestedActualDate->tm_mday;
    int m_month = TestedActualDate->tm_mon + 1;
    int m_year = TestedActualDate->tm_year + 1900;
    EXPECT_EQ(m_day, currentDate.getDay());
    EXPECT_EQ(m_month,currentDate.getMonth());
    EXPECT_EQ(m_year, currentDate.getYear());
};

//GTEST_API_;
