#include "csvfilereader.h"

#include <fstream>


CSVFileReader::CSVFileReader()
{
}

CSVFileReader::~CSVFileReader()
{
}

string CSVFileReader::removeWrongCharacters(string line) const
{
    string tmp;
    for (auto iterator{0}; iterator < line.length(); iterator++) {
        if (line[iterator] > 47) {
            tmp.push_back(line[iterator]);
        }
    }
    return tmp;
}

vector<string> CSVFileReader::readFile(string fileName) const
{
    ifstream csvFile(fileName);
    vector<string> receivedLines;
    string tmp;
    receivedLines.clear();
    while (getline(csvFile, tmp)) {
        string correctedLine{removeWrongCharacters(tmp)};
        if (correctedLine.length() != 0) {
        receivedLines.push_back(correctedLine);
        }
    }
    csvFile.close();
    return receivedLines;
}
