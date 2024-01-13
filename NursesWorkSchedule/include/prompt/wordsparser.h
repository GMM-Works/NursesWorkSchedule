#pragma once

#include "parser.h"

namespace std
{

class WordsParser : public iParser
{
public:
    WordsParser();
    ~WordsParser();

    std::vector<std::string> parseLine(std::string line) const override;

};

}

