#include <fstream>
#include <stdexcept>
#include <iostream>

#include "csvnursesreader.h"

CSVNursesReader::CSVNursesReader()
{
}

CSVNursesReader::~CSVNursesReader()
{
}

vector<Nurse> CSVNursesReader::readFile(string fileName) const
{
    fstream nursesFile;
    nursesFile.open(fileName);
    vector<Nurse> receivedNurses;
    string line;
    if (!nursesFile.is_open()) {
        throw std::runtime_error("can't open file " + fileName);
    }
    getline(nursesFile, line);
    while(getline(nursesFile, line)) {
        string firstname{""};
        string lastname{""};
        auto iterator{0};
        while (int(line[iterator]) < 0) {
            iterator++;
        }
        while (line[iterator] != ';') {
            firstname.push_back(line[iterator++]);
        }
        firstname.push_back('\0');
        ++iterator;
        while (line[iterator] != '\0') {
            lastname.push_back(line[iterator++]);
        }
        lastname.push_back('\0');
        receivedNurses.push_back(Nurse(firstname, lastname));
    }
    nursesFile.close();
    return receivedNurses;
}
