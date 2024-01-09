#pragma once

#include "filereader.h"

const auto WRONG_CHARACTERS_COUNT{3};

class CSVFileReader : public FileReader
{
public:
    CSVFileReader();
    ~CSVFileReader();

    string removeWrongCharacters(string line) const;
    vector<string> readFile(string fileName) const override;
};

