#pragma once

#include <string>
#include <vector>

class Procedure
{
public:
    virtual int execute(std::vector<std::string> arguments) = 0;
    virtual std::string getName() const = 0;
};

