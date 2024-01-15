//#include "windows.h"

#include "schedulecreator.h"

#pragma execution_character_set( "utf-8" )

int main(int argc, char* argv[])
{
    //SetConsoleCP(65001);
    //SetConsoleOutputCP(65001);

    //    string tmp;
    //    MainIO terminal("(wprowadź polecenie):");planCreator.readNurses(argv[0]);
    //    while (tmp != "quit") {
    //        terminal.printPrefix();
    //        tmp = terminal.getCommand();
    //    }

    //    CSVFileReader reader;
    //    vector<string> result = reader.readFile("pielegniarki.csv");

    //    CSVNursesParser parser;
    //    vector<Nurse> result2 = parser.parseNurses(result);

    //    CSVFileWriter writer;
    //    writer.open("something.csv");

    //    for (auto iterator{0}; iterator < result2.size(); ++iterator) {
    //        writer.writeLine(result2[iterator].getFirstname() + ";" + result2[iterator].getLastname());
    //    }

    // ScheduleCreator creator;
    // creator.readNurses("nurses.csv");
    // creator.readHolidays("holidays.csv");
    // creator.readStaff("staff.csv");
    // creator.generatePlan("nout.csv");
    // ProcedureConsole mainConsole("insert command:");
    // mainConsole.bindProcedure<ScheduleProcedure>();
    // while (true) {
    //     mainConsole.getCommand();
    // }

    ScheduleCreator planCreator;
    planCreator.readNurses(argv[1]);
    planCreator.readHolidays(argv[2]);
    planCreator.readStaff(argv[3]);
    planCreator.generatePlan(argv[4]);

    return 0;
}
