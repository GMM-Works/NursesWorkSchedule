#include <gtest/gtest.h>
#include "csvfilewriter.h"
#include "csvfilereader.h"
#include "nurse.h"
#include <string>
#include <vector>

class CSVFileFixtureTests : public ::testing::Test
{
protected:
    CSVFileWriter fileWriter;
    CSVFileReader fileReader;
};

TEST_F(CSVFileFixtureTests , FirstNurseTest){
    Nurse firstNurseTest = Nurse("Katarzyna","Kawka");
    fileWriter.open("Plik.csv");
    string text = firstNurseTest.getFirstname() + firstNurseTest.getLastname();
    fileWriter.writeLine(text);//not working
    vector<string> testedText = fileReader.readFile("Plik.csv");
    EXPECT_EQ(1,testedText.size());
}
