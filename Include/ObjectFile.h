#ifndef OBJECTFILE_H
#define OBJECTFILE_H
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class ObjectFile
{
    public:
        ObjectFile();
        void WriteFile(long progStart,long progLength,string progEnd,
                       ofstream &objectfileAddress, vector<string> records,string name);
        virtual ~ObjectFile();
    protected:
    private:
};

#endif // OBJECTFILE_H
