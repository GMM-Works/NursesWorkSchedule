#pragma once

#include <string>

using namespace std;

class FileWriter
{
public:
    virtual void open(string fileName) = 0;
    virtual void writeLine(string text) = 0;
    virtual void close() = 0;
};
