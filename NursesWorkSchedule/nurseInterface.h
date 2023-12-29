#pragma once

#include <string>

using namespace std;

class NurseInterface
{
public:
    string virtual getFirstname() const = 0;
    string virtual getLastname() const = 0;
    void virtual setFirstname(string name) = 0;
    void virtual setLastname(string name) = 0;

private:
    string m_firstname;
    string m_lastname;
};

