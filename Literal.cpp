#include <string>
#include <Literal.h>
#include "Literal.h"

using namespace std;
Literal::Literal()
{
}
void Literal::setString(string lit)
{
  literal = lit;
    if (lit[1] == 'X' || lit[1] == 'x')
        lenght = ( lit.length() - 4 ) / 2;
    else if (lit[1] == 'C' || lit[1] == 'c')
        lenght = lit.length() - 4;
}
