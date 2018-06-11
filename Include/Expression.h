#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
using namespace std;
class Expression
{
    public:
        Expression();
        bool ExpLabe(string lab);
        bool ExpInstraction(string inst);
        bool ExpOperant(string oper);
        bool ExpComment(string comm);
};

#endif // EXPRESSION_H
