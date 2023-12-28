#pragma once

#include "csvparser.h"
#include "holiday.h"

#include <vector>

class CSVHolidaysParser
{
public:
    CSVHolidaysParser();
    ~CSVHolidaysParser();

    vector<Holiday> parseHolidays(vector<string> lines) const;

private:
    CSVParser m_parser;
};
