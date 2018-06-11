#include "Opcode_SIC.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
Opcode_SIC::Opcode_SIC()
{
   ifstream input ("Map/SIC_opcode.txt");
   cin.rdbuf(input.rdbuf());
   if (input){
        string line ,index, code;
        while(getline(cin,line)){
            stringstream mycin(line);
            mycin >> index >> code;
            opcode[index] = code;
        }
   }
}
string Opcode_SIC::get_Opcode(string code)
{   if(opcode.find(code) == opcode.end()){
        return "";
    }
    return opcode[code];
}

