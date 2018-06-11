#include<iostream>
#include "ObjectFile.h"
#include "PassOne.h"
#include "ListingFile.h"



//include your files
using namespace std;
string generat_path(string path){
    string new_path = "";
    for (int i =0 ; path[i] != '\0' ; i++){
        new_path += path[i];
        if (path[i] == '/')
            new_path += '/';
    }
    return new_path;
}

int main()
{
    PassOne p_1;
    //make object of your class
    ListingFile L_1;
    string path;
    cout << "Enter the File path :" <<endl;
    cin >> path;
    path = generat_path(path);
    if (p_1.set_theFile_Path(path)){
       L_1.WriteFile(p_1);
    }
    return 0;
}
