#pragma once

#include "filereader.h"

const auto WRONG_CHARACTERS_COUNT{3};

class CSVFileReader : public FileReader
{
public:
    CSVFileReader();
    ~CSVFileReader();

    void removeWrongCharacters(ifstream &fileStream) const;
    vector<string> readFile(string fileName) const override;
};

