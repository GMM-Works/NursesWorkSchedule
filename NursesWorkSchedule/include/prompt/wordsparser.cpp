#include "wordsparser.h"

std::WordsParser::WordsParser()
{
}

std::WordsParser::~WordsParser()
{
}

std::vector<std::string> std::WordsParser::parseLine(std::string line) const
{
    std::vector<std::string> result;
    std::string tmp;
    for (auto iterator{0}; iterator < line.length(); iterator++) {
        if (line[iterator] == ' ') {
            result.push_back(tmp);
            tmp = "";
        } else {
            tmp += line[iterator];
        }
    }
    result.push_back(tmp);
    return result;
}
