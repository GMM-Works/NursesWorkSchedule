#include "windows.h"
#include "csvfilereader.h"
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

    CSVFileReader reader;
    vector<string> result = reader.readFile("pielegniarki.csv");
    for (auto iterator{0}; iterator < result.size(); iterator++) {
        cout << result[iterator] << endl;
    }

    /*
    CSVNursesReader reader;
    vector<Nurse> result = reader.readFile("pielegniarki.csv");
    for (auto iterator{0}; iterator < result.size(); iterator++) {
        cout << result[iterator].getFirstname() << " " << result[iterator].getLastname() << endl;
    }
    */
    getchar(); getchar();
    return 0;
}
