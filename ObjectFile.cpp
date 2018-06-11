#include "ObjectFile.h"
#include <string>
#include "stdlib.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>



ObjectFile::ObjectFile()
{
    //ctor
}
void ObjectFile::WriteFile(long progStart,long progLength,string progEnd,
                           ofstream &objectfileAddress,vector<string> records,
                           string name){

        //header
        stringstream aux1;
        stringstream aux2;
        stringstream aux3;
        aux1 << setfill('0') << setw(6) << hex << progStart;
        aux2 << setfill('0') << setw(6) << hex << progLength;
        aux3 << setfill(' ') << setw(6) << name;
        objectfileAddress << "H" << aux3.str() << aux1.str() << aux2.str() << endl;
        //text records
        vector<string>::iterator rec = records.begin();
        while(rec != records.end() ){
            objectfileAddress << "T" ;
            int counter = 0;
            string current ;
            while(counter <= 60 && rec != records.end()){
                current = *rec;
                counter += current.length();
                if(counter > 60){
                    counter -= current.length();
                    if(counter == 60){
                        break;
                    } else {
                        int z;
                        for(z = 0 ; z+counter <= 60 ;z++) {
                            objectfileAddress << current.at(z);
                        }
                        break;
                    }

                } else if (current == "\t") {
                    rec++;
                    break;
                } else {
                    objectfileAddress << current ;
                }
                rec++;
            }
            objectfileAddress << endl;
        }
        // End Record  -- we must still handle the presence of a label next to the END
    if(progEnd == " "){
      objectfileAddress << "E" << aux1.str() << endl ;
    } else {
      objectfileAddress << "E" << progEnd << endl;
    }
}

ObjectFile::~ObjectFile()
{
    //dtor
}
