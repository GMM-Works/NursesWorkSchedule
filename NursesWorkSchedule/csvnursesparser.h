#pragma once

#include "csvparser.h"
#include "nurse.h"

#include <vector>

class CSVNursesParser
{
public:
    CSVNursesParser();
    ~CSVNursesParser();

    vector<Nurse> parseNurses(vector<string> lines) const;

private:
    CSVParser m_parser;
};

