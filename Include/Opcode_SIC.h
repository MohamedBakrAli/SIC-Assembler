#ifndef OPCODE_SIC_H
#define OPCODE_SIC_H
#include <map>
#include <string>
using namespace std;
class Opcode_SIC
{
    public:
    Opcode_SIC();
    string get_Opcode(string code);
    private:
         map<string ,string> opcode;
};

#endif // OPCODE_SIC_H
