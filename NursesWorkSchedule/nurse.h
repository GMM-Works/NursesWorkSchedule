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
    string m_firstname;
    string m_lastname;
};

