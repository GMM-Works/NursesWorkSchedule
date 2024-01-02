#include <gtest/gtest.h>
#include "csvfilereader.h"
#include "csvfilewriter.h"
#include "nurse.h"
#include "csvnursesparser.h"
#include <string>
#include <vector>

class CSVFileReaderFixtureTests : public ::testing::Test
 {
 protected:
     CSVFileReader fileReader;
     CSVFileWriter fileWriter;
     CSVNursesParser csvNureParser;
     vector<Nurse> csvToTested;
 };
 TEST_F(CSVFileReaderFixtureTests , AddingDataToTest){
     fileWriter.open("nursesfiletest.csv");
     string text = "   Michal;Paszkiesz\nKamil;Ogorek\nKonrad;Smola\nEmil;Kasza\nAgnieszka;Chylinska";
     fileWriter.writeLine(text);
 }

TEST_F(CSVFileReaderFixtureTests , FirstFileReaderTest){
    csvToTested = csvNureParser.parseNurses(fileReader.readFile("nursesfiletest.csv"));
    ASSERT_EQ(5,csvToTested.size());
    EXPECT_EQ(csvToTested[0].getFirstname(),"Michal");
    EXPECT_EQ(csvToTested[1].getFirstname(),"Kamil");
    EXPECT_EQ(csvToTested[2].getFirstname(),"Konrad");
    EXPECT_EQ(csvToTested[3].getFirstname(),"Emil");
    EXPECT_EQ(csvToTested[4].getFirstname(),"Agnieszka");

    EXPECT_EQ(csvToTested[0].getLastname(),"Paszkiesz");
    EXPECT_EQ(csvToTested[1].getLastname(),"Ogorek");
    EXPECT_EQ(csvToTested[2].getLastname(),"Smola");
    EXPECT_EQ(csvToTested[3].getLastname(),"Kasza");
    EXPECT_EQ(csvToTested[4].getLastname(),"Chylinska");
}
