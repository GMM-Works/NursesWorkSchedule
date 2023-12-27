#include "windows.h"
#include "csvfilereader.h"
#include "csvnursesparser.h"
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

    CSVNursesParser parser;
    vector<Nurse> result2 = parser.parseNurses(result);

    for (auto iterator{0}; iterator < result2.size(); ++iterator) {
        cout << result2[iterator].getFirstname() << "," << result2[iterator].getLastname() << endl;
    }

    getchar(); getchar();
    return 0;
}
