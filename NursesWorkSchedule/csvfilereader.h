#include "filereader.h"

const auto WRONG_CHARACTERS_COUNT{3};

class CSVFileReader : public FileReader
{
public:
    CSVFileReader();
    ~CSVFileReader();

    void removeWrongCharacters(ifstream &fileStream);
    vector<string> readFile(string fileName) override;
};

