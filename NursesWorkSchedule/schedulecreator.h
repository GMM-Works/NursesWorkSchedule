#include "csvfilereader.h"
#include "csvnursesparser.h"
#include "csvholidaysparser.h"
#include "csvstaffparser.h"
#include "shift.h"
#include "currentdate.h"

#include <memory>

const int DAYS_OF_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class scheduleCreator
{
public:
    scheduleCreator();
    ~scheduleCreator();

    void readNurses(string CSVNursesFile);
    void readHolidays(string CSVHolidaysFile);
    void readStaff(string CSVHolidaysFile);
    void getDate();
    void generatePlan();

private:
    bool isYearLeap(int year) const;
    int dayOfPlan(int day, int month, int year) const;

private:
    vector<Holiday> m_holidays;
    vector<Nurse> m_nurses;
    vector<Staff> m_staffs;
    CSVHolidaysParser m_holidaysParser;
    CSVNursesParser m_nursesParser;
    CSVStaffParser m_staffParser;
    CSVFileReader m_reader;
    CurrentDate dateContainer;
    Shift m_shifts[30];
};

