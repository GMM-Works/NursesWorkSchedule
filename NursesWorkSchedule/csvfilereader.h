#pragma once

#include <string>
#include <vector>

#include "nurse.h"

using namespace std;

class CSVFileReader
{
public:
    virtual vector<Nurse> readFile(string fileName) const = 0;
};

