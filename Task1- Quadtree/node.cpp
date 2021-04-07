#include <iostream>

#ifndef NODE
    #define NODE
    #include "node.h"
#endif

using namespace std;

//Paramater-less Constructor
template <class Object>
node<Object>::node() {
}

/* x = x coordinate of the node
*  y = y coordinate of the node
*  status = boolean value of the node
*/

//Overloaded Constructor
template <class Object>
node<Object>::node(unsigned x, unsigned y, Object status){
    this->x = x;
    this->y = y;
    this->status = status;
}

// ----- Getters and Setters -----

template <class Object>
unsigned node<Object>::getX(){
    return this->x;
}

template <class Object>
void node<Object>::setX(unsigned x){
    this->x= x;
}

template <class Object>
unsigned node<Object>::getY(){
    return this->y;
}

template <class Object>
void node<Object>::setY(unsigned y){
    this->y = y;
}

template <class Object>
unsigned node<Object>::getStatus(){
    return this->status;
}

template <class Object>
Object node<Object>::setStatus(unsigned status){
    this->status = status;
}

//Prints the whole node
template <class Object>
void node<Object>::print(){
    this->status.print();
}
