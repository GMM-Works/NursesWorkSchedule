#pragma once

#include <string>

using namespace std;

class Parser
{
public:
    virtual string getPart(string& input) const = 0;
};
