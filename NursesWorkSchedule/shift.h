#include <string>
#include <vector>

using namespace std;

class Shift
{
public:
    Shift(vector<string> workers);
    ~Shift();

    vector<string> getWorkers() const;
    void addWorker(string name);
    int indexOf(string name) const;
    void removeAt(int index);

private:
    vector<string> m_workers;
};
