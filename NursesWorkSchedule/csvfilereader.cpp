#include "csvfilereader.h"

#include <fstream>


CSVFileReader::CSVFileReader()
{
}

CSVFileReader::~CSVFileReader()
{
}

void CSVFileReader::removeWrongCharacters(ifstream &fileStream) const
{
        fileStream.ignore(WRONG_CHARACTERS_COUNT);
}

vector<string> CSVFileReader::readFile(string fileName) const
{
    ifstream csvFile(fileName);
    vector<string> receivedLines;
    removeWrongCharacters(csvFile);
    string tmp;
    receivedLines.clear();
    while (getline(csvFile, tmp)) {
        receivedLines.push_back(tmp);
    }
    csvFile.close();
    return receivedLines;
}
