#include <gtest/gtest.h>
#include "csvfilewriter.h"
#include "csvfilereader.h"
#include "csvstaffparser.h"
#include "staff.h"
#include <string>
#include <vector>

class CSVStaffParserFixtureClass : public ::testing::Test
{
protected:
    CSVFileWriter fileWriter;
    CSVFileReader fileReader;
    CSVStaffParser staffParser;
};

TEST_F(CSVStaffParserFixtureClass , StaffParserFirstTest){
    fileWriter.open("testedstaff.csv");
    fileWriter.writeLine("   31;9;2024;2");
    fileWriter.writeLine("1;10;2024;3");
    fileWriter.close();
    vector<Staff> testedStaff = staffParser.parseStaff(fileReader.readFile("testedstaff.csv"));

    ASSERT_EQ( 2 , testedStaff.size() );

    EXPECT_EQ( 31 , testedStaff[0].getDay() );
    EXPECT_EQ( 9 , testedStaff[0].getMonth() );
    EXPECT_EQ( 2024 ,testedStaff[0].getYear() );
    EXPECT_EQ( 2 , testedStaff[0].getPersonsCount() );

    EXPECT_EQ( 1 , testedStaff[1].getDay() );
    EXPECT_EQ( 10 , testedStaff[1].getMonth() );
    EXPECT_EQ( 2024 , testedStaff[1].getYear() );
    EXPECT_EQ( 3 , testedStaff[1].getPersonsCount() );
}
