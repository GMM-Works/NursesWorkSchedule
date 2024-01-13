#include "include/prompt/procedure.h"
#include "schedulecreator.h"

class ScheduleProcedure : public Procedure
{
public:
    int execute(std::vector<std::string> arguments) override;
    std::string getName() const override;

private:
    ScheduleCreator creator;
};

