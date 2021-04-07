#include <iostream>

#ifndef BOOLEAN
    #define BOOLEAN
    #include "boolean.h"
#endif

#ifndef FILE
    #define FILE
    #include "file.cpp"
#endif

#ifndef NODE
    #define NODE
    #include "node.cpp"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "quadtree.cpp"
#endif

using namespace std;
using namespace colour;

//parameterless constructor
boolean::boolean(){
}

//overloaded constructor
boolean::boolean(string status){
    this->setStatus(status);
}

void boolean::setStatus(string status){
    this->validate(status);
    this->status = status[0];
}

void boolean::validate(string status){
    char argc = status[0];
    if(!(argc == 'T' || argc == 'F' || argc == '\n')){
        cout << "Unacceptable character" << endl;
    }
}

bool boolean::getBool() const{
    if(this->status.compare("T") == 0){
        return true;
    }
    else{
        return false;
    }
}

string boolean::getStatus() const{
    return this->status;
}

bool boolean::operator== (const boolean &boolean) const{
    return (boolean.getStatus() == this->status);
}

//Printing the Boolean
void boolean::print(){
    if(this->getBool()){
        cout << "T" << endl;
    }
    else{
        cout << "F" << endl;
    }
}

//Parsing and Returning a Quadtree
quadtree<boolean>*boolean::parse(unsigned l, unsigned chars, ifstream &name){
    quadtree<boolean>* qt = new quadtree<boolean>(chars, l); //initializing the quadtree
    for(int i=0; i<l; i++){
        for(int j=0; j<chars; j++){
            char argc;
            name.get(argc);
            if(argc != '\n'){
                boolean tempbool;
                tempbool.setStatus(string(1,argc));
                qt->insert(new node<boolean>(i,j,tempbool));
            }
        }
    }
    return qt;
}

boolean boolean::parseLine(string l){
    string ret = l.substr(l.find_last_of(file<boolean>::DELIMETER) + 1);
    return boolean(ret);
}

