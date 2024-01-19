#include "windows.h"

#include "schedulecreator.h"

#pragma execution_character_set( "utf-8" )

int main(int argc, char* argv[])
{
    ScheduleCreator planCreator;
    planCreator.readNurses(argv[1]);
    planCreator.readHolidays(argv[2]);
    planCreator.readStaff(argv[3]);
    planCreator.generatePlan(argv[4]);

    return 0;
}
