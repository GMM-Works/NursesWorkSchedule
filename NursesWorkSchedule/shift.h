#pragma once

#include "nurse.h"

#include <string>
#include <vector>

using namespace std;

class Shift
{
public:
    Shift();
    ~Shift();

    vector<Nurse> getNurses() const;
    int indexOf(Nurse nurse) const;
    void addNurse(Nurse nurse);
    Nurse nurseAt(int index) const;
    void removeAt(int index);
    void clearNurses();

private:
    vector<Nurse> m_nurses;
};
