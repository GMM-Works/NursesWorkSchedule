#include <gtest/gtest.h>
#include "csvfilereader.h"
#include <string>
#include <vector>

class CSVFileReaderFixtureTests : public ::testing::Test
{
protected:
    CSVFileReader fileReader;
};

TEST_F(CSVFileReaderFixtureTests , FirstFileReaderTest){
    vector<string> textToTested = fileReader.readFile("Plik2.csv");
    EXPECT_EQ(4,textToTested.size());
}
