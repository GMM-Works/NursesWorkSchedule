#pragma once

#include <string>

using namespace std;

class Nurse
{
public:
    Nurse(string firstname, string lastname);
    ~Nurse();

    string getFirstname() const;
    string getLastname() const;

private:
    const string m_firstname;
    const string m_lastname;
};

