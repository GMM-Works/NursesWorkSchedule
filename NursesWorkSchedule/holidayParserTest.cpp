#include <gtest/gtest.h>
#include "csvfilewriter.h"
#include "csvfilereader.h"
#include "csvholidaysparser.h"
#include "holiday.h"
#include <string>
#include <vector>

class CSVHolidayParserFixtureTests : public ::testing::Test
{
protected:
    CSVFileWriter fileWriter;
    CSVFileReader fileReader;
    CSVHolidaysParser holidayParser;
};

TEST_F(CSVHolidayParserFixtureTests , HolidayParserFirstTest){
    fileWriter.open("testedholiday.csv");
    fileWriter.writeLine("   Mateusz;Borkowski;31;9;2024");
    fileWriter.writeLine("Marianna;Kawulska;1;10;2024");
    fileWriter.close();
    vector<Holiday> testedHolidays = holidayParser.parseHolidays(fileReader.readFile("testedholiday.csv"));

    ASSERT_EQ( 2 , testedHolidays.size() );

    EXPECT_EQ( "Mateusz" , testedHolidays[0].getFirstname() );
    EXPECT_EQ( "Borkowski" , testedHolidays[0].getLastname() );
    EXPECT_EQ( 31 , testedHolidays[0].getDay() );
    EXPECT_EQ( 9 , testedHolidays[0].getMonth() );
    EXPECT_EQ( 2024 , testedHolidays[0].getYear() );

    EXPECT_EQ( "Marianna" , testedHolidays[1].getFirstname() );
    EXPECT_EQ( "Kawulska" , testedHolidays[1].getLastname() );
    EXPECT_EQ( 1 , testedHolidays[1].getDay() );
    EXPECT_EQ( 10 , testedHolidays[1].getMonth() );
    EXPECT_EQ( 2024 , testedHolidays[1].getYear() );
}
