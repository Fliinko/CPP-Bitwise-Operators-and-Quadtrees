#include <vector>

#ifndef NODE
    #define NODE
    #include "node.h"
#endif

template <class Object>
class quadtree{

    private:
        unsigned width;
        unsigned height;
        unsigned x;
        unsigned y;
        unsigned level;

        vector<node<Object> *> results;
        bool flag = false;
        bool isParent = false;
        quadtree * children[4];

    public:
        quadtree(unsigned width, unsigned height);
        quadtree(unsigned width, unsigned height, unsigned level);
        quadtree(unsigned width, unsigned height, unsigned x, unsigned y, unsigned level);

        unsigned getWidth();
        void setWidth(unsigned width);
        unsigned getHeight();
        void setHeight(unsigned height);
        unsigned getX();
        void setX(unsigned x);
        unsigned getY();
        void setY(unsigned y);
        unsigned getLevel();
        void setLevel(unsigned level);

        void insert(node<Object> * leaf);
        Object get(unsigned x, unsigned y);
        void save(string n);

};