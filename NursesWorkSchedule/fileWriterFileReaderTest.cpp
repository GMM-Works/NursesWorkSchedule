#include <gtest/gtest.h>
#include "csvfilewriter.h"
#include "csvfilereader.h"
#include "csvnursesparser.h"
#include "nurse.h"
#include <string>
#include <vector>

class CSVFileFixtureTests : public ::testing::Test
{
protected:
    CSVFileWriter fileWriter;
    CSVFileReader fileReader;
    CSVNursesParser nurseParser;
};

TEST_F(CSVFileFixtureTests , FirstWriterTest){
    Nurse firstNurseTest = Nurse("Katarzyna","Kawka");
    fileWriter.open("nursesWriteFile.csv");
    string text = "   "+firstNurseTest.getFirstname() + ";" + firstNurseTest.getLastname() ;
    fileWriter.writeLine(text);
}

TEST_F(CSVFileFixtureTests , FirstReaderTest){
    Nurse firstNurseTest = Nurse("Katarzyna","Kawka");
    vector<Nurse> testedNurse = nurseParser.parseNurses(fileReader.readFile("nursesWriteFile.csv"));
    ASSERT_EQ(1,testedNurse.size());
    EXPECT_EQ(firstNurseTest.getFirstname(), testedNurse[0].getFirstname() );
    EXPECT_EQ(firstNurseTest.getLastname(), testedNurse[0].getLastname());
}
