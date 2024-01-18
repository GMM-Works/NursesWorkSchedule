#include "shift.h"

Shift::Shift()
{
}

Shift::~Shift()
{
}

vector<Nurse> Shift::getNurses() const
{
    return m_nurses;
}

int Shift::indexOf(Nurse nurse) const
{
    for (auto iterator{0}; iterator < m_nurses.size(); ++iterator) {
        if (m_nurses[iterator].getFirstname() == nurse.getFirstname() && m_nurses[iterator].getLastname() == nurse.getLastname()) {
            return iterator;
        }
    }
    return -1;
}

void Shift::addNurse(Nurse nurse)
{
    m_nurses.push_back(nurse);
}

Nurse Shift::nurseAt(int index) const
{
    return m_nurses[index];
}

void Shift::removeAt(int index)
{
    for (auto iterator{index}; iterator < m_nurses.size() - 1; ++iterator) {
        m_nurses[iterator] = m_nurses[iterator + 1];
    }
}

void Shift::clearNurses()
{
    m_nurses.clear();
}
