#ifndef LINEOFCODE_H
#define LINEOFCODE_H
#include <string>
#include "Expression.h"
using namespace std;
class LineOfCode
{
    public:
        LineOfCode();
        void set_Line(string line);
        string tolower_case(string s);
        string get_formate_line();
        string get_comment_line();
        string get_lable();
        string get_inst();
        string get_oper();
        string get_comm();
        bool line();
        bool commentLine();
        bool lable();
        bool comment();
        bool instruction();
        bool operat();
    private:
        Expression ex;
        string get_space(int n);
        string format_line;
        string Com_line = "";
        string lab = "";
        string com = "";
        string inst = "";
        string opera = "";
        bool Com_line_bool = false;
        bool lable_bool = false;
        bool com_bool = false;
        bool inst_bool = false;
        bool opera_bool = false;
};

#endif // LINEOFCODE_H
