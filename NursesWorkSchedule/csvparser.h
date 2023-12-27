#pragma once

#include "parser.h"

class CSVParser : public Parser
{
public:
    CSVParser(char separator);
    ~CSVParser();

    string getPart(string& input) const override;

private:
    char m_separator;
};
