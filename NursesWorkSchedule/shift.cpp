#include "shift.h"

Shift::Shift(vector<string> workers)
    : m_workers(workers)
{
}

Shift::~Shift()
{
}

vector<string> Shift::getWorkers() const
{
    return m_workers;
}

void Shift::addWorker(string name)
{
    m_workers.push_back(name);
}

int Shift::indexOf(string name) const
{
    for (auto iterator{0}; iterator < m_workers.size(); ++iterator) {
        if (m_workers[iterator] == name) {
            return iterator;
        }
    }
    return -1;
}

void Shift::removeAt(int index)
{
    for (auto iterator{index}; iterator < m_workers.size() - 1; ++iterator) {
        m_workers[iterator] = m_workers[iterator + 1];
    }
}
