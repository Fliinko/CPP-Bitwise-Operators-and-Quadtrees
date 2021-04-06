#include <fstream>
#include <string>
#include <iostream>

#ifndef BOOLEAN
    #define BOOLEAN
    #include "boolean.h"
#endif

#ifndef FILE
    #define FILE
    #include "file.h"
#endif

#ifndef FILE_CPP
    #define FILE_CPP
    #include "file.cpp"
#endif

#ifndef BNW
    #define BNW
    #include "bnw.h"
#endif

#ifndef NODE
    #define NODE
    #include "node.h"
#endif

#ifndef NODE_CPP
    #define NODE_CPP
    #include "node.cpp"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "quadtree.h"
#endif

#ifndef QUADTREE_CPP
    #define QUADTREE_CPP
    #include "quadtree.cpp"
#endif

using namespace std;
using namespace colour;

void Menu(){

    cout << "Welcome to the Menu: " << endl;
    cout << "1. Load Filename" << endl;
    cout << "2. Save Filename" << endl;
    cout << "3. Show Quadtree" << endl;
    cout << "4. Quit" << endl;
}

void ShowTypes(){

    cout << "Options: " << endl;
    cout << "1. \tBoolean: " << endl;
    cout << "2. \tBlack and White: " << endl;
}

string getPrompt(string line){
    unsigned pos;
    if((pos = line.find(" ")) != string::npos){
        return line.substr(0,pos);
    }
    else{
        return line;
    }
}

string getFileType(string line){
    unsigned x,y;

    x = line.find(" ");
    y = line.find_last_of(" ");

    if((x == string::npos) && (y == string::npos)){ //There is no type
        return string("");
    }
    else if(x == y){ //Parameter is only the filename
        return string("");
    }
    else{
        return line.substr(x+1, y-x-1);
    }
}

string getFileName(string line){
    unsigned x;
    x = line.find_last_of(" ");

    if(x == string::npos){ //There is no type
        return string("");
    }
    else{
        return line.substr(x+1);
    }
}

string toLower(string argc){
    string lwr = "";
    for(int i=0; i<argc.length(); i++){
        lwr += tolower(argc[i]);
    }
    return lwr;
}

int main(int argc, char ** argv){
    cout << "Kindly enter the file like this: command [type] [filename] " << endl;
    Menu();
    ShowTypes();

    string userinput;
    bool quadtree_yn = false; //if quadtree exists or not

    string quadtree_type = "";
    string cmd = "", type = "", name = "";

    quadtree<boolean> * bool_qt = new quadtree<boolean>(0,0);
    quadtree<bnw> * bnw_qt = new quadtree<bnw>(0,0);

    do{
        cout << "Enter your command: ";
        getline(cin, userinput);
        userinput = toLower(userinput);
        cmd = getPrompt(userinput);
        type = getFileType(userinput);
        name = getFileName(userinput);

        /*cout << "1. Load Filename" << endl;
        * cout << "2. Save Filename" << endl;
        * cout << "3. Show Quadtree" << endl;
        * cout << "4. Quit" << endl; */

       if(cmd.compare("load") == 0){

           if(type.compare("boolean") == 0){

               bool_qt = file<boolean>::load(name);
               quadtree_type = "boolean";
               quadtree_yn = true;
               cout << name << "Loaded" << endl;

           }else if(type.compare("black and white") == 0){

               bnw_qt = file<bnw>::load(name);
               quadtree_type = "black and white";
               quadtree_yn = true;
               cout << name << "Loaded" << endl;
           }
           else{

               cout << "Unrecognized Type!" << endl;
               ShowTypes();
           }

       }else if(cmd.compare("save") == 0){

           if(quadtree_type.compare("boolean") == 0){

               file<boolean>::save(*bool_qt, name);
               cout << "Quadtree saved to location -> " << name << endl;
           }
           else if(quadtree_type.compare("black and white") == 0){

               file<bnw>::save(*bnw_qt, name);
               cout << "Quadtree saved to location -> " << name << endl;
           }
           else{
               cout << "Unrecognized Type!" << endl;
               ShowTypes();
           }

       }else if(cmd.compare("show") == 0){
           if(quadtree_yn){
               if(quadtree_type.compare("boolean") == 0){
                   bool_qt->print();
               }else if(quadtree_type.compare("black and white") == 0){
                   bnw_qt->print();
               }
           } else {
               cout << "No quadtree loaded" << endl;
           }
       } else if(cmd.compare("quit") != 0){
           cout << "Unknown command!" << endl;
           Menu();
       }
        
    } while(cmd.compare("quit") != 0);
}