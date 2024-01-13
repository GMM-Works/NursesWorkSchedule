#include "storage.h"

extern std::ProcedureConsole* CURRENT_PROCEDURE_CONSOLE;

void std::setStorage(std::string variable, std::string value)
{
    (CURRENT_PROCEDURE_CONSOLE)->setStorage(variable, value);
}

std::string std::getStorage(string variable)
{
    return (CURRENT_PROCEDURE_CONSOLE)->getStorage(variable);
}
