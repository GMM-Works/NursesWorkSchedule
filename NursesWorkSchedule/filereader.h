#pragma once

#include <string>
#include <vector>

using namespace std;

class FileReader
{
public:
    virtual vector<string> readFile(string fileName) = 0;
};
