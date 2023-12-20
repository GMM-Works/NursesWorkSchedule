#pragma once

#include "csvfilereader.h"

class CSVNursesReader : public CSVFileReader
{
public:
    CSVNursesReader();
    ~CSVNursesReader();

    vector<Nurse> readFile(string fileName) const override;
};

