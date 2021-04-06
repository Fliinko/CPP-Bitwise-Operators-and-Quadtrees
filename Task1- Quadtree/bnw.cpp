//Black and White (B N W)
#include <iostream>

#ifndef FILE
    #define FILE
    #include "file.cpp"
#endif

#ifndef BLACKNWHITE
    #define BLACKNWHITE
    #include "bnw.h"
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

//Parameterless Constructor
bnw::bnw(){}

//Overloaded Constructor
bnw::bnw(string status){
    this->setStatus(status);
}

void bnw::setStatus(string status){
    this->validate(status);
    this->status = status;
}

string bnw::getStatus() const{
    return this->status;
}

bool bnw::operator== (const bnw &colour) const{
    return (this->getStatus().compare(colour.getStatus()) == 0);
}

void bnw::validate(string argc){
    locale argv;
    for(int i =0; i < argc.length(); i++){
        char c = tolower(argc[i], argv);
        if(!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f')){
            cout << "Invalid Input" << endl;
        }
    }
}

void bnw::print(){
    if(this->status.compare("ff") == 0){
        cout << "WHITE" << endl;
    }
    else if(this->status.compare("00") == 0){
        cout << "BLACK" << endl;
    }
    else{
        cout << this->status << endl;
    }
}

quadtree<bnw> * quadtree::parse(unsigned l, unsigned chars, ifstream &name){
    quadtree<bnw>*quadtree = new quadtree<bnw>(chars/2,l);
    for(int i =0; i<l; i++){
        string line;
        getline(name,line);

        for(int j = 0; j <chars/2; j++){
            bnw obj = bnw();
            obj.setStatus(line.substr(j * 2 + 0, 2));
            quadtree->insert(new node<bnw>(j, i, obj));
        }
    }
    return quadtree;
}

bnw bnw::parseLine(string line){
    string status = line.substr(line.find_last_of(file<boolean>::DELIMETER) + 1);
    return bnw(status);
}