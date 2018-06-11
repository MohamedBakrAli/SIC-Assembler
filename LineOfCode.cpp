#include "LineOfCode.h"
#include <sstream>
#include <iostream>

using namespace std;
LineOfCode::LineOfCode(){}
void LineOfCode::set_Line(string line)
{
    format_line = "";
    string temp;
    stringstream mycin (line);
    if (line[0] == '.'){
        format_line = line;
        Com_line = line;
        Com_line_bool = true;
    }
    else if (line[0] == ' ' || line[0] == '\t'){
        format_line += '!';
        format_line += get_space(8);
        lable_bool = false;
        lab = "";
        opera = "";
        mycin >> inst >> opera;
        com = "";
        while (mycin >> temp){
            com += " ";
            com += temp;
        }
        if (inst[0] == '.'){
            format_line = line;
            Com_line = line;
            Com_line_bool = true;
        }
        else {
            Com_line_bool = false;
            if (ex.ExpInstraction(inst)){
                inst_bool = true;
                format_line += inst;
                format_line += get_space(8 - inst.length());
            }
            else {
                inst_bool = false;
               format_line += "Error   ";
            }
            if (ex.ExpOperant(opera) || opera == ""){
                opera_bool = true;
                format_line += opera;
                format_line += get_space(19 - opera.length());
            }
            else {
                opera_bool = false;
                format_line += "Error              ";
            }
            if (ex.ExpComment(com) || com == ""){
                com_bool = true;
                format_line += com;
                format_line += get_space(31-com.length());
            }
            else {
                com_bool = false;
                format_line += "Error                          ";
            }
        }

    }
    else {
        Com_line_bool = false;
        mycin >> lab >> inst >> opera;
        com = "";
        while (mycin >> temp){
            com += " ";
            com += temp;
        }
        if (ex.ExpLabe(lab)){
            lable_bool = true;
            format_line += lab;
            format_line += get_space(9 - lab.length());
        }
        else {
            lable_bool = false;
            format_line += "Error    ";
        }
        if (ex.ExpInstraction(inst)){
            inst_bool = true;
            format_line += inst;
            format_line += get_space(8 - inst.length());
        }
        else {
            inst_bool = false;
            format_line += "Error   ";
        }
        if (ex.ExpOperant(opera)){
            opera_bool = true;
            format_line += opera;
            format_line += get_space(19 - opera.length());
        }
        else {
            opera_bool = false;
            format_line += "Error              ";
        }
        if (ex.ExpComment(com)){
            com_bool = true;
            format_line += com;
            format_line += get_space(31 - com.length());
        }
        else {
            com_bool = false;
            format_line += "Error                          ";
        }
    }
}
bool LineOfCode::line()
{
    if (Com_line_bool)
        return true;
    else {
        if (lab != "" && com != "")
            return lable_bool && inst_bool && opera_bool && com_bool;
        else if (lab == "" && com != "")
            return inst_bool && opera_bool && com_bool;
        else if (lab != "" && com == "")
            return lable_bool && inst_bool && opera_bool;
        else if (lab == "" && com != "" && opera == ""){
            if (tolower_case(inst)== "ltorg"){
                return com_bool;
            }
            return false;
        }
        else if (lab == "" && com == "" && opera == ""){
            if (tolower_case(inst) == "ltorg"){
                return true;
            }
            return false;
        }
        else
            return inst_bool && opera_bool;
    }
}
bool LineOfCode::lable()
{
    return lable_bool;
}
bool LineOfCode::instruction()
{
    return inst_bool;
}
bool LineOfCode::operat()
{
    return opera_bool;
}
bool LineOfCode::comment()
{
    return com_bool;
}
bool LineOfCode::commentLine()
{
    return Com_line_bool;
}
string LineOfCode::get_comment_line()
{
    if (Com_line_bool)
        return Com_line;
    return "";
}
string LineOfCode::get_lable()
{
    if (lable_bool)
        return lab;
    return "";
}
string LineOfCode::get_inst()
{
    if (inst_bool || inst == "!")
        return tolower_case(inst) ;
    return "";
}
string LineOfCode::get_oper()
{
    if (opera_bool)
        return opera;
    return "";
}
string LineOfCode::get_comm()
{
    if (com_bool)
        return com;
    return "";
}
string LineOfCode::get_space(int n)
{
    string temp = "";
    while (n--)
        temp += " ";
    return temp;
}
string LineOfCode::get_formate_line()
{
    return format_line;
}
string LineOfCode::tolower_case(string s)
{
    for(int i = 0; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
        }
        return s;
}
