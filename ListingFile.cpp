#include "ListingFile.h"
#include "PassOne.h"
#include "LineOfCode.h"
#include "Opcode_SIC.h"
#include<sstream>
#include<fstream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include "ObjectFile.h"

using namespace std;
ListingFile::ListingFile()
{

}
void ListingFile::WriteFile(PassOne first_pass){
    string line;
    bool FlagContinue = true;
    string addressPath = first_pass.get_path_to_address();
    LineOfCode formatter;
    Opcode_SIC opcodeTable;
    unsigned found = addressPath.find_last_of("/\\");
    string absPath = addressPath.substr(0,found+1);
    string name = addressPath.substr(found+9,addressPath.length());
    string path = absPath + "Listing_" + name;
    string path2 = absPath + "Object_" + name;
    ofstream listingFile (path.c_str());
    ofstream objectfile (path2.c_str());
    ifstream in(first_pass.get_path_to_address().c_str());
    streambuf *cinbuf = std::cin.rdbuf();
    cin.rdbuf(in.rdbuf());
    if (in){
        long proStart = first_pass.get_program_start();
        long proSize = first_pass.get_program_size();
        string proEnd;
        while(getline(cin,line)){
            int i = 1;
            while (line[i] != ' '&& line[i] != '\t'){
                i++;
            }
            while (line[i] == ' '|| line[i] == '\t'){
                i++;
            }
          string tempLine = line.substr(i,line.length());
          formatter.set_Line(tempLine);
          string instruction = formatter.get_inst();
          string objectCode;
          if(formatter.tolower_case(instruction) == "resw" || formatter.tolower_case(instruction) == "resb"){
                objectCode = "\t";
                records.push_back(objectCode);
                 objectCode = "";
          }else if (formatter.tolower_case(instruction) == "start"){
              objectCode ="";
          } else if (formatter.tolower_case(instruction) == "ltorg"){
              objectCode ="";
          }else if (formatter.tolower_case(instruction) == "equ"){
              objectCode ="";
          }else if (formatter.tolower_case(instruction) == "org"){
              objectCode ="";
          } else if (formatter.tolower_case(instruction) == "word"){
              string temp = formatter.get_oper();
              stringstream buffer;
              long P = first_pass.conver_string_to_int(temp);
              buffer << setfill('0') << setw(6) << hex << P;
              temp = buffer.str();
              objectCode = temp;
              records.push_back(objectCode);
          } else if (formatter.tolower_case(instruction) == "byte"){
              string temp = formatter.get_oper();
              stringstream buffer;
              string sentence = "";
              if(temp[0] == 'C'|| temp[0] == 'c'){
                    int i = 2;
                    while(temp[i] != '\''){
                        sentence += temp[i];
                        i++;
                    }
                    objectCode = "";
                    for(int i = 0 ; i<sentence.length();i++){
                        buffer << hex << sentence.at(i);
                        temp = buffer.str();
                        objectCode+=temp;

                    }
                  stringstream aux;
                  aux << setfill('0') << setw(6) << hex << objectCode;
                  objectCode = aux.str();
                  records.push_back(objectCode);

              } else {
                  int i = 2;
                  while(temp[i] != '\''){
                    sentence += temp[i];
                      i++;
                  }
                  stringstream aux;
                  aux << setfill('0') << setw(6) << hex << sentence;
                  objectCode = aux.str();
                  records.push_back(objectCode);
              }
          } else if (formatter.tolower_case(instruction) == "end") {
              string operand = formatter.get_oper();
              if(operand == " " || operand == "\t"){
                  stringstream aux;
                  aux << setfill('0') << setw(6) << hex << proStart;
                  objectCode = aux.str();
                  proEnd = " ";
              } else {
                  long long int labelAddress = first_pass.get_lable_address(formatter.get_oper());
                  if(labelAddress == -1 ) {
                      listingFile << "Error in label definition" << endl;
                      FlagContinue = false;
                  }
                  stringstream aux;
                  proEnd = to_string(labelAddress);
                  aux << setfill('0') << setw(6) << proEnd;
                  objectCode = aux.str() ;
              }
          } else if (formatter.get_inst() == "!"){
              string temp = formatter.get_oper();
              stringstream buffer;
              string sentence = "";
              if(temp[1] == 'C'|| temp[1] == 'c'){
                  int i = 3;
                  while(temp[i] != '\'') {
                      sentence += temp[i];
                      i++;
                  }
                  objectCode = "";
                  for(int i = 0 ; i<sentence.length();i++){
                      buffer << hex << (int)sentence.at(i);


                  }
                  temp = buffer.str();
                  objectCode+=temp;
                  stringstream aux;
                  aux << setfill('0') << setw(6) << hex << objectCode;
                  objectCode = aux.str();
                  records.push_back(objectCode);

              } else {
                  int i = 3;
                  while(temp[i] != '\''){
                      sentence += temp[i];
                      i++;
                  }
                  stringstream aux;
                  aux << setfill('0') << setw(6) << hex << sentence;
                  objectCode = aux.str();
                  records.push_back(objectCode);
              }
          } else {
          string operatorCode =  opcodeTable.get_Opcode(formatter.get_inst());
              stringstream aux;
              if(operatorCode == ""){
                  listingFile << "Error in Opcode definition"<<endl;
                  FlagContinue = false;
              }
              string z = formatter.get_oper().substr(0,2);
              if(z == "=X" ||z == "=x"||z == "=C"||z == "=c" ){
                  Literal  literall = first_pass.get_literal(formatter.get_oper());
                  if(literall.literal == ""){
                      listingFile << "Error in literal definition" << endl;
                      FlagContinue = false;
                  }
                      stringstream buffer;
                      buffer << hex << literall.address;
                      string litAddress = buffer.str();
                      aux << setfill('0') << setw(6) << operatorCode+litAddress;

              } else {
                  long long int labelAddress;
                  string indexed = formatter.get_oper().substr(formatter.get_oper().length()-2,2);
                  if(indexed ==",X" || indexed == ",x"){
                       // index = contents of index register
                      labelAddress = first_pass.get_lable_address(formatter.get_oper().
                      substr(0,formatter.get_oper().length()-2));

                  } else{
                      labelAddress = first_pass.get_lable_address(formatter.get_oper());
                  }
                  if(labelAddress == -1 ) {
                      listingFile << "Error in label definition" << endl;
                      FlagContinue = false;
                    }
                  aux << setfill('0') << setw(6) << GenerateObjectCode(operatorCode,labelAddress);
              }

              objectCode = aux.str();
              records.push_back(objectCode);
          }
            if(objectCode == ""){
                listingFile << line << endl;
            } else {
                listingFile << line << objectCode << endl;
            }
        }
        if(FlagContinue) {
            ObjectFile objectMaker;
            objectMaker.WriteFile(proStart, proSize, proEnd, objectfile, records, name);
        }
    }
    cout << "-->pass two terminated []_[]" <<endl;
}

string ListingFile::GenerateObjectCode(string opcode,long long literalAddress){
  stringstream buffer;
  buffer << hex << literalAddress;
  string objectCode = opcode + buffer.str();
    return objectCode;
}

string ListingFile::fill_zeroes(string name)
{
    string temp = "";
    long n = 6 - name.length();
    temp = name;
    while (n--)
        temp += '0';
    return temp;
}


ListingFile::~ListingFile()
{
    //dtor
}
