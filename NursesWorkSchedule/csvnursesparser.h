#pragma once

#include "csvparser.h"
#include "nurse.h"

#include <vector>

using namespace std;

const char SEPARATING_CHARACTER{';'};

class CSVNursesParser
{
public:
    CSVNursesParser();
    ~CSVNursesParser();

    vector<Nurse> parseNurses(vector<string> lines) const;

private:
    CSVParser m_parser;
};

