#include <string>

using namespace std;

class IO
{
public:
    virtual void printPrefix() const = 0;
    virtual string getCommand() const = 0;
};

