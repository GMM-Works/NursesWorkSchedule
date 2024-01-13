#include "scheduleprocedure.h"

#include <iostream>

using namespace std;

int ScheduleProcedure::execute(std::vector<std::string> arguments)
{
    string nursesFile, holidaysFile, staffFile, outputFile;
    cout << "insert name of file with nurses:" << endl;
    cin >> nursesFile;
    cout << "insert name of file with holidays:" << endl;
    cin >> holidaysFile;
    cout << "insert name of file with staff count:" << endl;
    cin >> staffFile;
    cout << "insert name of output file:" << endl;
    cin >> outputFile;
    creator.readNurses(nursesFile);
    creator.readHolidays(holidaysFile);
    creator.readStaff(staffFile);
    creator.generatePlan(outputFile);
    return 0;
}

std::string ScheduleProcedure::getName() const
{
    return "generateplan";
}
