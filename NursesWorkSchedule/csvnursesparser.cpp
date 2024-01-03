#include "csvnursesparser.h"

#include <iostream>

CSVNursesParser::CSVNursesParser()
    : m_parser(SEPARATING_CHARACTER)
{
}

CSVNursesParser::~CSVNursesParser()
{
}

vector<Nurse> CSVNursesParser::parseNurses(vector<string> lines) const
{
    vector<Nurse> parsedNurses;

    for (auto iterator{0}; iterator < lines.size(); ++iterator) {
        string currentLine{lines[iterator]};
        string firstName = m_parser.getPart(currentLine);
        string lastName = m_parser.getPart(currentLine);
        parsedNurses.push_back(Nurse(firstName, lastName));
    }

    return parsedNurses;
}
