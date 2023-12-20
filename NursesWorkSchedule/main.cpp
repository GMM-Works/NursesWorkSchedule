#include "windows.h"
#include "csvnursesreader.h"
#include "mainio.h"

#include <iostream>

#pragma execution_character_set( "utf-8" )

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    string tmp;
    MainIO terminal("(wprowadź polecenie):");
    while (tmp != "quit") {
        terminal.printPrefix();
        tmp = terminal.getCommand();
    }
    CSVNursesReader reader;
    vector<Nurse> result = reader.readFile("pielegniarki.csv");
    for (auto iterator{0}; iterator < result.size(); iterator++) {
        cout << result[iterator].getFirstname() << " " << result[iterator].getLastname() << endl;
    }
    return 0;
}
