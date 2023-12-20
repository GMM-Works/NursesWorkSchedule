#include <iostream>

#include "mainio.h"

MainIO::MainIO(const string prefix)
    : m_prefix(prefix)
{
}

MainIO::~MainIO()
{
}

void MainIO::printPrefix() const
{
    cout << m_prefix;
}

string MainIO::getCommand() const
{
    string receivedCommand;
    cin >> receivedCommand;
    return receivedCommand;
}
