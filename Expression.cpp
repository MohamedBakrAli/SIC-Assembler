#include "Expression.h"
#include <iostream>

using namespace std;
Expression::Expression()
{
}
bool Expression::ExpLabe(string lab)
{
    int len = lab.length();
    if (len < 9 )
    {
        if ((lab[0] >= 'A' && lab[0] <= 'Z')||(lab[0] >= 'a' && lab[0] <= 'z')||(lab[0] == '_')){
            for (int i = 1; i < len; i++){
                if (!((lab[i] >= 'A' && lab[i] <= 'Z')||(lab[i] >= 'a' && lab[i] <= 'z')||(lab[i] == '_')||
                (lab[i] >= '0'&& lab[i] <= '9')||lab[i] == '_'))
                return false;
            }
            return true;
        }
        else
            return false;
    }
    return false;
}
bool Expression::ExpInstraction(string inst)
{
    int len = inst.length();
    if (len < 7)
    {
        for (int i=0;i<len;i++){
            if ((inst[i] >= 'A' && inst[i] <= 'Z')||(inst[i] >= 'a' && inst[i] <= 'z')){
                continue;
            }
            return false;
        }
        return true;
    }
    return false;
}
bool Expression::ExpOperant(string oper)
{
    int len = oper.length();
    if (len < 19)
    {
        if (oper == "*")
            return true;
        int x = oper.find_first_of(',');
        int pl = oper.find_first_of('+' );
        int mn = oper.find_first_of('-');
        if (x != -1){
            string l = oper.substr(0,x);
            if (ExpLabe(l) && len-x==2 && (oper[x+1] == 'X' || oper[x+1] == 'x'))
                return true;
            return false;
        }
        else {
            if (pl != -1|| mn != -1){
                int l;
                if (pl != -1)
                    l = pl;
                else
                    l = mn;
                string s1 = oper.substr(0,l);
                string s2 = oper.substr(l+1,len);
                if (s1[0] >= '0' && s1[0] <= '9'){
                    for (int i = 1; i < s1.length(); i++){
                        if (!(s1[i] >= '0' && s1[i] <= '9'))
                            return false;
                    }
                } else if (s1[0] == '='&& (s1[1] == 'X' || s1[1] == 'x')&& s1[2] == '\''){
                    int y = s1.find_last_of('\'');
                    if (y != 1 && s1.length() < 7)
                        return true;
                    return false;
                }else if (s1[0] == '='&& (s1[1] == 'C' || s1[1] == 'c')&& s1[2] == '\''){
                    int y = s1.find_last_of('\'');
                    if (y != 1 && s1.length() < 11)
                        return true;
                    return false;
                }
                else {
                    if (!ExpLabe(s1))
                        return false;
                }
                if (s2[0] >= '0' && s2[0] <= '9'){
                    for (int i =1; i < s2.length() ; i++){
                        if (!(s2[i] >= '0' && s2[i] <= '9'))
                            return false;
                    }
                }else if (s2[0] == '='&& (s2[1] == 'X' || s2[1] == 'x')&& s2[2] == '\''){
                    int y = s2.find_last_of('\'');
                    if (y != 1 && s2.length() < 7)
                        return true;
                    return false;
                }else if (s2[0] == '='&& (s2[1] == 'C' || s2[1] == 'c')&& s2[2] == '\''){
                    int y = s2.find_last_of('\'');
                    if (y != 1 && s2.length() < 11)
                        return true;
                    return false;
                }
                else {
                    if (!ExpLabe(s2))
                        return false;
                }
                return true;
            } else if (oper[0] >= '0' && oper[0] <= '9'){
                for (int i =1 ;i < len; i++){
                    if (!(oper[i] >= '0' && oper[i] <= '9'))
                        return false;
                }
                return true;
            } else if (oper[0] == 'C' || oper[0] == 'c'&&(oper[1] == '\'')){
                int y = oper.find_last_of('\'');
                if (y != 1 && oper.length() < 4)
                    return true;
                return false;
            } else if (oper[0] == 'X' || oper[0] == 'x'&&(oper[1] == '\'')){
                 int y = oper.find_last_of('\'');
                  if (y != 1 && oper.length() < 7)
                    return true;
                return false;
            } else if ((oper[0] == '=')&&oper[1] == 'C' || oper[1] == 'c'&&(oper[2] == '\'')){
                int y = oper.find_last_of('\'');
                if (y != 1 && oper.length() < 8)
                    return true;
                return false;
            } else if ((oper[0] == '=')&&oper[1] == 'X' || oper[1] == 'x'&&(oper[2] == '\'')){
                int y = oper.find_last_of('\'');
                if (y != 1 && oper.length() < 11)
                    return true;
                return false;
            } else {
                return ExpLabe(oper);
            }
        }
    }
    return false;
}
bool Expression::ExpComment(string comm)
{
    if (comm.length() > 31)
        return false;
    return true;
}
