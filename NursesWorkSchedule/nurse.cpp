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

void Nurse::setFirstname(string name)
{
    this->m_firstname = name;
}

void Nurse::setLastname(string name)
{
    this->m_lastname = name;
}

bool Nurse::operator==(Nurse other) const
{
    if (other.getFirstname() == this->getFirstname() && this->getLastname() == other.getLastname()) {
        return true;
    }
    return false;
}
