#pragma once

#include <string>
#include <vector>

class iParser
{
public:
    virtual std::vector<std::string> parseLine(std::string line) const = 0;
};


