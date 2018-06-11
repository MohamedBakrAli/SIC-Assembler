#ifndef LISTINGFILE_H
#define LISTINGFILE_H
#include <string>
#include "PassOne.h"
#include <vector>
using namespace std;
class ListingFile
{
    public:
        ListingFile();
        void WriteFile(PassOne first_Pass);
        virtual ~ListingFile();
    protected:
    private:
        string GenerateObjectCode(string opcode , long long literalAddress);
        string fill_zeroes(string value);
        vector<string> records;
};

#endif // LISTINGFILE_H
