#include "nurse.h"

Nurse::Nurse(string firstname, string lastname)
    : m_firstname(firstname)
    , m_lastname(lastname)
{
}

Nurse::~Nurse()
{
}

string Nurse::getFirstname() const
{
    return m_firstname;
}

string Nurse::getLastname() const
{
    return m_lastname;
}
