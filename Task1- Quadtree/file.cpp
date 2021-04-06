#include <fstream>
#include <iostream>
#include <string>

#ifndef FILE
    #define FILE
    #include "file.h"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "quadtree.h"
#endif

using namespace std;

template <class Object>
const string file<Object>::DELIMETER = string("|"); //Seperate coords when saving/loading files

//Load File
template <class Object>
file<Object>::file(string name){
    string filetype = name.substr(name.find_last_of(".") + 1) //Getting file type (.txt)
    if(filetype == "txt"){ //If the extension is .txt
        if(ifstream(name)){ //If the name exists in the directory
            this->tempfile.open(name);
        }
        else{
            cout << "The file" << name << "does not exist";
        }
    }
    else{
        cout << filetype << "is not a compatible file type" << endl;
    }
}

//Closing File
template <class Object>
file<Object>::~file(){
    this->file.close();
}

//Parsing the File
template<class Object>
quadtree<Object>*file<Object>::getQuadTree(){
    unsigned argc = this->getLines();
    unsigned argcLen = this->getLineLen();
    this->tempfile.clear();
    this->tempfile.seekg();
    return Object::parse(argc, argcLen, this->tempfile);
}

//Saving the Quadtree in the File
template <class Object>
void file<Object>::save(quadtree<Object> &quadtree, string name){
    if(name.find_last_of('.') == string::npos){
        name += ".4";
    }else if(name.substr(name.find_last_of(".") + 1).compare("4") != 0){
        cout << "Extension is incorrect" << endl;
    }

    ofstream file1;
    file1.open(name, ios::out);
    unsigned w = quadtree.getWidth();
    unsigned h = quadtree.getHeight();

    file1 << w << endl;
    file1 << h << endl;

    file.close();
}

//Loading the File
template <class Object>
quadtree<Object>*file<Object>::load(string name){
     if(name.find_last_of('.') == string::npos){
        name += ".4";
    }else if(name.substr(name.find_last_of(".") + 1).compare("4") != 0){
        cout << "Extension is incorrect" << endl;
    }

    ifstream file1;
    file1.open(name, ios::in); //Creates a file if it doesn't already exist

    if(file1.is_open()){
        unsigned w,h = 0;
        string ws, hs;

        getline(file1, ws);
        getline(file1, hs);

        w = stoi(ws);
        h = stoi(hs);

        quadtree<Object>*quadtree = new quadtree<Object>(w,h);
        for(int i = 0; i < w*h; i++){
            unsigned val1, val2;
            string line;
            getline(file1, line);

            val1 = stoi(line.substr(0,line.find(file<Object>::DELIMETER)))
            val2 = stoi(line.substr(line.find(file<Object>::DELIMETER) + 1, line.find_last_of(file<Object>::DELIMETER)));
            Object obj = Object::parseLine(line);

            node<Object>*tempnode = new node<Object>(val1, val2, obj);
            quadtree->insert(tempnode);
        }
        file1.close();
        return quadtree;
    }
    else{
        cout << file1 << "Not found" << endl;
    }
}

//Printing the File
template <class Object>
void file<Object>::print(){
    this->tempfile.clear();
    this->tempfile.seekg(0);

    string line;
    while(!getline(this->tempfile, line). eof()){
        if(line.length() > 0){
            cout << line << endl;
        }
    }
}

template <class Object>
unsigned file<Object>::getLineLen(){
    this->tempfile.clear();
    this->tempfile.seekg(0);

    string l;
    getline(this->tempfile, l);
    return l.length();
}

template <class Object>
unsigned file<Object>::getLines(){
    this->tempfile.clear();
    this->tempfile.seekg(0);
    unsigned lines = 0;
    string l;

    while(!getline(this->tempfile, l). eof()){
        lines++;
    }

    return lines;
}