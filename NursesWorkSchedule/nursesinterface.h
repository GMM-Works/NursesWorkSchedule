#pragma once

#include <string>

using namespace std;

class NursesInterface
{
public:
    virtual string getFirstname() const = 0;
    virtual string getLastname() const = 0;
    virtual void setFirstname(string name) = 0;
    virtual void setLastname(string name) = 0;
};
