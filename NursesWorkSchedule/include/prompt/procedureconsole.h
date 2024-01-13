#pragma once

#include "wordsparser.h"
#include "procedure.h"

#include <memory>

namespace std
{
const std::string COLORS[] = {"black", "blue", "green", "cyan", "red", "magenta", "brown", "lightgray", "darkgray", "lightblue", "lightgreen", "lightcyan", "lightred", "lightmagenta", "yellow", "white" };
const auto DEFAULT_CONSOLE_COLOR{15};

struct Variable
{
    string name;
    string value;
};

class ProcedureConsole
{
public:
    ProcedureConsole();
    ProcedureConsole(std::string prefix);
    ~ProcedureConsole();

    int getCommand();
    std::vector<std::string> getLastCommand() const;
    void setPrefix(std::string prefix);
    void flush();
    template <typename ProcedureType>
    void bindProcedure()
    {
        m_procedures.push_back(std::make_unique<ProcedureType>());
    };

    void setStorage(std::string variable, std::string value);

    std::string getStorage(std::string variable) const;

private:
    std::vector<std::unique_ptr<Procedure>> m_procedures;
    std::vector<std::string> m_lastCommand;
    std::vector<Variable> m_storage;
    WordsParser m_parser;
    std::string m_prefix;
};

void changeConsoleColor(std::string color);

void changeConsoleColor(int color);

void resetConsoleColor();
}
