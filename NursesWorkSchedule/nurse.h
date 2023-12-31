#pragma once

#include <string>

#include "nursesinterface.h"

using namespace std;

class Nurse : public NursesInterface
{
public:
    Nurse(string firstname, string lastname);
    ~Nurse();

    string getFirstname() const override;
    string getLastname() const override;
    void setFirstname(string name) override;
    void setLastname(string name) override;

private:
    string m_firstname;
    string m_lastname;
};

