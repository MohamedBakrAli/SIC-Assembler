#ifndef LITERAL_H
#define LITERAL_H
#include <iostream>

using namespace std;
class Literal
{
    public:
        Literal();
        void setString(string lit);
        string literal;
        long long address;
        long long lenght;
};

#endif // LITERAL_H
