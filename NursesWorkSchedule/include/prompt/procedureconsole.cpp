//#include "windows.h"

#include "procedureconsole.h"

#include <iostream>

// const auto COLOR_HANDLE{GetStdHandle(STD_OUTPUT_HANDLE)};

// std::ProcedureConsole* CURRENT_PROCEDURE_CONSOLE = nullptr;

// std::ProcedureConsole::ProcedureConsole()
//     : m_prefix("")
// {
// }

std::ProcedureConsole::ProcedureConsole(std::string prefix)
    : m_prefix(prefix)
{
}

std::ProcedureConsole::~ProcedureConsole()
{
}

int std::ProcedureConsole::getCommand()
{
    //CURRENT_PROCEDURE_CONSOLE = this;
    std::cout << m_prefix;
    std::string command;
    getline(std::cin, command);
    m_lastCommand = m_parser.parseLine(command);
    for (auto iterator{0}; iterator < m_procedures.size(); ++iterator) {
        if (m_procedures[iterator]->getName() == m_lastCommand[0]) {
            std::vector<std::string> args(m_lastCommand.begin() + 1, m_lastCommand.end());
            return m_procedures[iterator]->execute(args);
        }
    }
    return -1;
}

std::vector<std::string> std::ProcedureConsole::getLastCommand() const
{
    return m_lastCommand;
}

void std::ProcedureConsole::setPrefix(std::string prefix)
{
    m_prefix = prefix;
}

void std::ProcedureConsole::flush()
{
    m_procedures.clear();
}

void std::ProcedureConsole::setStorage(string variable, string value)
{
    for (auto iterator{0}; iterator < m_storage.size(); ++iterator) {
        if (m_storage[iterator].name == variable) {
            m_storage[iterator].value = value;
            return;
        }
    }
    std::Variable var;
    var.name = variable;
    var.value = value;
    m_storage.push_back(var);
    return;
}

std::string std::ProcedureConsole::getStorage(string variable) const
{
    for (auto iterator{0}; iterator < m_storage.size(); ++iterator) {
        if (m_storage[iterator].name == variable) {
            return m_storage[iterator].value;
        }
    }
    return NULL;
}

// void std::changeConsoleColor(string color)
// {
//     for (auto iterator{0}; iterator < sizeof(COLORS) / sizeof(COLORS[0]); ++iterator) {
//         if (color == COLORS[iterator]) {
//             SetConsoleTextAttribute(COLOR_HANDLE, iterator);
//         }
//     }
// }

// void std::changeConsoleColor(int color)
// {
//     SetConsoleTextAttribute(COLOR_HANDLE, color);
// }

// void std::resetConsoleColor()
// {
//     SetConsoleTextAttribute(COLOR_HANDLE, DEFAULT_CONSOLE_COLOR);
// }
