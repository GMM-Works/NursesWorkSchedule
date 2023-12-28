#include "csvfilereader.h"
#include "csvfilewriter.h"
#include "csvnursesparser.h"
#include "csvholidaysparser.h"
#include "shift.h"

#include <memory>

class scheduleCreator
{
public:
    scheduleCreator();
    ~scheduleCreator();

    void generatePlan(string CSVNursesFile, string CSVHolidaysFile);

private:
    vector<Holiday> m_holidays;
    vector<Nurse> m_nurses;
    CSVHolidaysParser m_holidaysParser;
    CSVFileReader m_reader;
    CSVNursesParser m_nursesParser;
    Shift m_shifts[30];
};

