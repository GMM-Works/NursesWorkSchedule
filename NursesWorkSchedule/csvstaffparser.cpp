#include "csvstaffparser.h"

CSVStaffParser::CSVStaffParser()
    : m_parser(SEPARATING_CHARACTER)
{
}

CSVStaffParser::~CSVStaffParser()
{
}

vector<Staff> CSVStaffParser::parseStaff(vector<string> lines) const
{
    vector<Staff> parsedStaffs;
    for (auto iterator{0}; iterator < lines.size(); ++iterator) {
        string currentLine{lines[iterator]};
        int day = stoi(m_parser.getPart(currentLine));
        int month = stoi(m_parser.getPart(currentLine));
        int year = stoi(m_parser.getPart(currentLine));
        int personsCount = stoi(m_parser.getPart(currentLine));
        parsedStaffs.push_back(Staff(personsCount, day, month, year));
    }
    return parsedStaffs;
}
