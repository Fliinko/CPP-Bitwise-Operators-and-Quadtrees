#include <iostream>
#include <fstream>
#include <string>

#ifndef NODE
    #define NODE
    #include "node.h"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "quadtree.h"
#endif

using namespace std;

//Setting up the QuadTree with a given width and height
template <class Object>
quadtree<Object>::quadtree(unsigned width, unsigned height){
    this->width = width;
    this->height = height;
    this->x = 0;
    this->y = 0;
    this->level = 0;
}

//Setting an overloaded constructor for QuadTree
template <class Object>
quadtree<Object>::quadtree(unsigned width, unsigned height, unsigned x, unsigned y, unsigned level){
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->level = level;
}

//----- Getters and Setters -----

//Width 
template <class Object>
unsigned quadtree<Object>::getWidth(){
    return this->width;
}

template <class Object>
void quadtree<Object>::setWidth(unsigned width){
    this->width = width;
}

//Height
template <class Object>
unsigned quadtree<Object>::getHeight(){
    return this->height;
}

template <class Object>
void quadtree<Object>::setHeight(unsigned height){
    this->height = height;
}

//x
template <class Object>
unsigned quadtree<Object>::getX(){
    return this->x;
}

template <class Object>
void quadtree<Object>::setX(unsigned x){
    this->x = x;
}

//y
template <class Object>
unsigned quadtree<Object>::getY(){
    return this->y;
}

template <class Object>
void quadtree<Object>::setY(unsigned y){
    this->y = y;
}

//Level
template <class Object>
unsigned quadtree<Object>::getLevel(){
    return this->level;
}

template <class Object>
void quadtree<Object>::setLevel(unsigned level){
    this->level = level;
}

// ---------------------------------------

//----- Quadtree Operations -----

//Insert into Quadtree
template <class Object>
void quadtree<Object>::insert(node<Object>*leaf){
    if(leaf->getX() >= (this->x + this->width) || leaf->getY() >= (this->y + this->height) || leaf->getX() < 0 || leaf->getY() < 0){ //Leaf is out of bounds
        cout << "This element is out of bounds: " << this->x << this->y << endl;
    }
    else if(!this->flag && !this->isParent){
        this->results.push_back(leaf); //insert new value into quadtree
        this->isParent = true; //update flag to show that this quadtree now is a parent
    }
    else if(!this->flag && this->isParent){
        node<Object>*first_node = ((node<Object>*)(this->results.front())); //sets first_node as the first child of the quadtree
        if(first_node->getStatus() == leaf->getStatus()){
            this->results.push_back(leaf); //added to list of node children
        }
        else if(this->width > 1 && this->height > 1){
            this->flag = true;
            this->isParent = false;

            this->children[0] = new quadtree(this->width/2, this->height/2, this->x, this->y, this->level +1); //init NW
            this->children[1] = new quadtree(this->width - this->width/2, this->height/x, this->x + this->width/2, this->y, this->level +1); //init NE
            this->children[2] = new quadtree(this->width/2, this->height - this->height/2, this->x, this-> y + this->height/2, this->level +1); //init SW
            this->children[3] = new quadtree(this->width - this->width/2, this->height - this->height/2, this->x + this->width/2, this->y + this->height/2, this->level+1); //init SE

            for(int i = 0; i < this->results.size(); i++){
                this->insert(this->results.at(i))
            }
            this->insert(leaf);
            this->results.clear(); //remove all instances 
        }
        else{
            this->results.push_back(leaf); //add to the list of node children
        }
    } else if(this->flag){
        if (leaf->getX() < (this->x + this->width/2) && leaf->getY() < (this->y + this->height/2)) { 
            this->children[0]->insert(leaf); //NW QuadTree
        } else if (leaf->getX() >= (this->x + this->width/2) && leaf->getY() < (this->y + this->height/2)) { 
            this->children[1]->insert(leaf; //NE QuadTree
        } else if (leaf->getX() < (this->x + this->width/2) && leaf->getY() >= (this->y + this->height/2)) { 
            this->children[2]->insert(leaf); //SW QuadTree
        } else if (leaf->getX() >= (this->x + this->width/2) && leaf->getY() >= (this->y + this->height/2)) { 
            this->children[3]->insert(leaf); //SE QuadTree
        }
    }
}

//Get from Quadtree
template <class Object>
Object quadtree<Object>::get(unsigned x, unsigned y){
    if(x > (this->x + this->width) || y > (this->y + this->height || x < 0 || y < 0)){
        cout << "Coordinate: " << x << "x" << y << "y" <<"is out of bounds" << endl;
    }
    else if(this->flag){
        if(x < (this->x + this->width/2) && y < (this->y + this->height/2)){
            return this->children[0]->get(x,y); //getting val for NW
        }
        else if(x >= (this->x + this->width/2) && y < (this->y + this->height/2)){
            return this->children[1]->get(x,y); //getting val for NE
        }
        else if(x < (this->x + this->width/2) && y >= (this->y + this->height/2)){
            return this->children[2]->get(x,y); //getting val for SW
        }
        else if(x >= (this->x + this.width/2) && y >= (this->y + this->height/2)){
            return this->children[3]->get(x,y); //getting val for SE
        }
    }
    else if(!this->flag && this->isParent){
        for(int i = 0; this->results.size(); i++){
            node<Object>* temp = this->results.at(i);
            if(temp->getX() == x && temp->getY() == y){
                return temp->getStatus()
            }
        }
    }
    else{
        cout << "Coordinate: " << x << "x" << y << "y" <<"is out of bounds" << endl;
    }
    return Object();
}

//Saving the Quadtree
template <class Object>
void quadtree<Object>::save(string n){
    ofstream openfile(n + ".4", ios::binary); //open or create file
    openfile.write((char *)&this->width, sizeof(this->width));
    openfile.write((char *)&this->height, sizeof(this->height));

    for(int i = 0; i< this->width; i++){
        for(int j = 0; j< this->height; j++){
            openfile.write((char *)&i, sizeof(i));
            openfile.write((char *)&j, sizeof(j));
            Object obj = this->get(i,j);
            openfile.write((char *)&obj, sizeof(obj));
        }
    }
    openfile.close();
}
