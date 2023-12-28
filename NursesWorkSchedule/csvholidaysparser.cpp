#include "csvholidaysparser.h"

CSVHolidaysParser::CSVHolidaysParser()
    : m_parser(SEPARATING_CHARACTER)
{
}

CSVHolidaysParser::~CSVHolidaysParser()
{
}

vector<Holiday> CSVHolidaysParser::parseHolidays(vector<string> lines) const
{
    vector<Holiday> parsedHolidays;
    for (auto iterator{0}; iterator < lines.size(); ++iterator) {
        string currentLine{lines[iterator]};
        string firstName = m_parser.getPart(currentLine);
        string lastName = m_parser.getPart(currentLine);
        int day = stoi(m_parser.getPart(currentLine));
        int month = stoi(m_parser.getPart(currentLine));
        int year = stoi(m_parser.getPart(currentLine));
        parsedHolidays.push_back(Holiday(firstName, lastName, day, month, year));
    }
    return parsedHolidays;
}
