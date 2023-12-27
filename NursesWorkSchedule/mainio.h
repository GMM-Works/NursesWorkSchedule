#pragma once

#include "io.h"

class MainIO : public IO
{
public:
    MainIO(const string prefix);
    ~MainIO();

    void printPrefix() const override;
    string getCommand() const override;

private:
    const string m_prefix;
};

