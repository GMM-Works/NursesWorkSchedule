//#include "windows.h"
#include "csvfilereader.h"
#include "csvfilewriter.h"
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

    CSVFileWriter writer;
    writer.open("something.csv");

    for (auto iterator{0}; iterator < result2.size(); ++iterator) {
        writer.writeLine(result2[iterator].getFirstname() + ";" + result2[iterator].getLastname());
    }

    getchar(); getchar();
    return 0;
}
