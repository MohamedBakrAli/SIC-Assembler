#ifndef PASSONE_H
#define PASSONE_H
#include<Literal.h>
#include <iostream>
#include <map>
using namespace std;
class PassOne
{
    public:
        PassOne();
        bool set_theFile_Path(string path);
        long long  get_lable_address(string lab);
        Literal get_literal(string lit);
        long long  get_program_size();
        long long  get_program_start();
        string get_path_to_address();
        int conver_string_to_int(string s);
    private:
        map<string , long long> address;
        map<string ,Literal> littab;
        string path_to_address;
        long long org_equ(string oper, int line_number);
        long long counter = 0;
        long long start;
        bool flag = true;
};

#endif // PASSONE_H
