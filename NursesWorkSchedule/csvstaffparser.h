#include "csvparser.h"
#include "staff.h"

#include <vector>

class CSVStaffParser
{
public:
    CSVStaffParser();
    ~CSVStaffParser();

    vector<Staff> parseStaff(vector<string> lines) const;

private:
    CSVParser m_parser;
};
