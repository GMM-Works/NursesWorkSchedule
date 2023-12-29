#include "csvfilereader.h"
#include "csvfilewriter.h"
#include "csvnursesparser.h"
#include "csvholidaysparser.h"
#include "shift.h"
#include "currentdate.h"

#include <memory>

class scheduleCreator
{
public:
    scheduleCreator();
    ~scheduleCreator();

    void readNurses(string CSVNursesFile);
    void readHolidays(string CSVHolidaysFile);
    void getDate();
    void generatePlan();

private:
    vector<Holiday> m_holidays;
    vector<Nurse> m_nurses;
    CSVHolidaysParser m_holidaysParser;
    CSVFileReader m_reader;
    CSVNursesParser m_nursesParser;
    CurrentDate dateContainer;
    Shift m_shifts[30];
};

