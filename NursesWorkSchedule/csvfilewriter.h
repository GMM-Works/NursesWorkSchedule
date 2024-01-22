#pragma once

#include "filewriter.h"

#include <fstream>

class CSVFileWriter : public FileWriter
{
public:
    CSVFileWriter();
    CSVFileWriter(string fileName);
    ~CSVFileWriter();

    void close() override;
    void open(string fileName) override;
    void writeLine(string text) override;
    void write(string text);

private:
    ofstream m_output;
};

