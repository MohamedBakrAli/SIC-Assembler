#include "PassOne.h"
#include "LineOfCode.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Opcode_SIC.h"
#include <sstream>
#include <map>
#include <set>
#include "Literal.h"


using namespace std;
PassOne::PassOne(){}
bool PassOne::set_theFile_Path(string path)
{
    string line;
    string op;
    set<string> lit_set;
    LineOfCode line_code;
    int str_flag = 0;
    int end_flag = 0;
    bool flag_str = true;
    flag = true;
    int line_number = 0;
    Opcode_SIC opcode = Opcode_SIC();
    ifstream in(path.c_str());
    streambuf *cinbuf = std::cin.rdbuf();
    cin.rdbuf(in.rdbuf());
    if (in){
        unsigned found = path.find_last_of("/\\");
        string realPath = path.substr(0,found+1);
        string name = path.substr(found+1);
        string path_1 ,path_2;
        path_1 = realPath + "Address_" + name;
        path_to_address = path_1;
        path_2 = realPath + "Format_" + name;
        ofstream addressFile (path_1.c_str());
        ofstream formateFile(path_2.c_str());
        while(getline(cin,line)){
            line_number++;
            line_code.set_Line(line);
            formateFile << line_code.get_formate_line()<<endl;
            if (!line_code.line()){
                cout << "-->Error in syntax in line :" << line_number <<endl;
                flag = false;
            }
            if (!line_code.commentLine()){
                if (line_code.tolower_case(line_code.get_inst()) == "start"){
                    str_flag ++;
                    counter = conver_string_to_int(line_code.get_oper());
                    map<string, long long>::iterator i = address.find(line_code.get_lable());
                    if (i == address.end()){
                        address[line_code.get_lable()] = counter;
                    }
                    else {
                        address[line_code.get_lable()] = counter;
                        cout << "-->double definition for the start lable in line:"<<line_number<<endl;
                        flag = false;

                    }
                    start = counter;
                    addressFile << hex  << counter<<"\t"<< line_code.get_formate_line() <<endl;
                }
                else {
                    if (str_flag == 0 && flag_str){
                        cout << "-->there is no start for this program !" << endl;
                        flag =  false;
                        flag_str = false;
                    }
                    op = line_code.tolower_case(line_code.get_inst());
                    if (line_code.lable() && (op != "equ")){
                        map<string,long long>::iterator i = address.find(line_code.get_lable());
                        if (i == address.end()){
                            address[line_code.get_lable()] = counter;
                        }
                        else {
                            address[line_code.get_lable()] = counter;
                            cout << "-->double definition in line:"<<line_number<<endl;
                            flag = false;
                        }
                    }
                    if (op == "end"){
                        end_flag ++;
                        addressFile<< hex <<counter << "\t" << line_code.get_formate_line() << endl;
                    }
                    else if (op == "byte"){
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        counter += counter += line_code.get_oper().length() - 3;
                    }
                    else if (op == "word"){
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        counter += 3;
                    }
                    else if (op == "resw"){
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        counter += (3 * conver_string_to_int(line_code.get_oper()));
                    }
                    else if (op == "resb"){
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        counter += conver_string_to_int(line_code.get_oper());
                    }
                    else if (opcode.get_Opcode(op) != ""){
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        counter += 3;
                        if (line_code.get_oper()[0] == '='){
                            lit_set.insert(line_code.get_oper());
                        }
                    }
                    else if (op == "ltorg"){
                        Literal l;
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        for (set<string>::iterator it = lit_set.begin(); it != lit_set.end() ; ++it){
                            map<string,Literal>::iterator i = littab.find(*it);
                            if (i == littab.end()){
                                l.setString(*it);
                                formateFile << "*        !       " << *it <<"                                           "<<endl;
                                addressFile << hex << counter << "\t" <<  "*        !       " << *it <<"                                           "<<endl;
                                counter += l.lenght;
                                l.address = counter;
                                littab[*it] = l;
                            }
                        }
                        lit_set.clear();
                    }
                    else if (op == "org"){
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        string oper = line_code.get_oper();
                        counter = org_equ(oper, line_number);
                    }
                    else if (op == "equ"){
                        addressFile << hex <<counter << "\t" << line_code.get_formate_line() << endl;
                        if (line_code.get_lable() == ""){
                            cout << "-->there is no lable before EQU in line:"<<line_number<<endl;
                            flag = false;
                        }
                        map <string, long long>::iterator i = address.find(line_code.get_lable());
                        if (i != address.end()){
                            cout << "-->double definition in line:"<<line_number<<endl;
                            flag = false;
                        }
                        string oper = line_code.get_oper();
                        address[line_code.get_lable()] = org_equ(oper, line_number);

                    }
                    else {
                        cout << "-->invalid opcode ( "<< op <<" )check format file in line :"<<line_number<< endl;
                        addressFile << "###" << "\t" << line_code.get_formate_line() << endl;
                        flag =  false    ;
                    }
                }
            }
        }
        if (str_flag > 1){
            cout << "-->there is ( " << str_flag << " ) start for this program!\n";
            flag = false;
        }
        if (end_flag == 0){
            cout  << "-->there is no end for this program !" << endl;
            flag =  false;
        }
        else if (end_flag > 1){
            cout << "-->there is ( " << end_flag << " ) end for this program!\n";
            flag = false;
        }
        Literal l;
        for (set<string>::iterator it = lit_set.begin(); it != lit_set.end() ; ++it){
            map<string,Literal>::iterator i = littab.find(*it);
            if (i == littab.end()){
                l.setString(*it);
                formateFile << "*        !       " << *it <<"                                           "<<endl;
                addressFile << hex << counter << "\t" <<  "*        !       " << *it <<"                                            "<<endl;
                counter += l.lenght;
                l.address = counter;
                littab[*it] = l;
            }
        }
        if (! flag){
            cout << "-->pass one failed ^-^";
            return false;
        }
        cout << "-->pass one done ^-^" << endl;
        return true;
    }
    else {
        cout << "-->File is not exit!\n";
        return false;
    }
}
long long PassOne::get_lable_address(string lab)
{ if(address.find(lab) == address.end()){
        return -1 ;
    }
   return address[lab];
}
int PassOne::conver_string_to_int(string s)
{
    int n = 0;
    stringstream my(s);
    my >> n;
    return n;
}
long long PassOne::get_program_size()
{
    return counter - start;
}
long long PassOne::get_program_start()
{
    return start;
}
string PassOne::get_path_to_address(){
return path_to_address;
}
Literal PassOne::get_literal(string lit){
    if(littab.find(lit) == littab.end()){
        Literal temp;
        temp.setString("");
        return  temp;
    }
    return littab[lit];
}
long long PassOne::org_equ(string oper, int line_number)
{
    long long cnt;
    int pl = oper.find_first_of('+');
    int mn = oper.find_first_of('-');
    if (pl!= -1 || mn != -1){
        int add1,add2;
        int len;
        if (pl == -1)
            len = mn;
        else
            len = pl;
        string s1 = oper.substr(0,len);
        string s2 = oper.substr(len+1,oper.length());
        if (s1[0] == '='){
            map<string,Literal>::iterator i = littab.find(s1);
            if (i != littab.end()){
                add1 = littab[s1].address;
            }
            else {
                flag = false;
                cout << "-->forward reference is not allowed in line:"<<line_number<<endl;
            }
        }
        else if (s1[0] >= '0' && s1[0] <= '9') {
            add1 = conver_string_to_int(s1);
        }else if (s1[0] == '*'){
            add1 = counter;
        }
        else {
            map<string , long long>::iterator i = address.find(s1);
            if (i != address.end()){
                add1 = address[s1];
            }
            else {
                flag = false;
                cout << "-->forward reference is not allowed in line:"<<line_number<<endl;
            }
        }
        if (s2[0] == '='){
            map<string,Literal>::iterator i = littab.find(s2);
            if (i != littab.end()){
                add2 = littab[s2].address;
            }
            else {
                flag = false;
                cout << "-->forward reference is not allowed in line:"<<line_number<<endl;
            }
        }
        else if (s2[0] >= '0' && s2[0] <= '9'){
            add2 = conver_string_to_int(s2);
        }
        else if (s1[0] == '*'){
            add2 = counter;
        }
        else {
            map<string , long long>::iterator i = address.find(s2);
            if (i != address.end()){
                add2 = address[s2];
            }
            else {
                flag = false;
                cout << "-->forward reference is not allowed in line:"<<line_number<<endl;
            }
        }
        if (pl != -1)
            cnt = add1 + add2;
        else
            cnt = add1 - add2;
        if (cnt < 0)
            cout << "-->negative addressing in line:"<<line_number<<endl;
    }
    else if (oper[0]>= '0' && oper[0] <= '9'){
        cnt = conver_string_to_int(oper);
    }
    else if (oper[0] == '='){
        map<string,Literal>::iterator i = littab.find(oper);
        if (i != littab.end()){
            cnt = littab[oper].address;
        }
        else {
            flag = false;
            cout << "-->forward reference is not allowed in line:"<<line_number<<endl;
        }
    }
    else if (oper[0] == '*'){
        cnt = counter;
    }
    else {
        map<string , long long>::iterator i = address.find(oper);
        if (i != address.end()){
            cnt = address[oper];
        }
        else {
            flag = false;
            cout << "-->forward reference is not allowed in line:"<<line_number<<endl;
        }
    }
    return  cnt;
}