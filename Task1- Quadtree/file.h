#include <fstream>
#include <string>
#include <vector>

#ifndef QUADTREE
    #define QUADTREE
    #include "quadtree.h"
#endif

template<typename Object>
class file{

    private:
        ifstream tempfile;

        unsigned getLineLen();
        unsigned getLines();

    public:
        static const string DELIMETER;

        file(string name);
        ~file();

        quadtree<Object> * getQuadTree();

        void save(quadtree<Object> &quadtree, string name);
        static quadtree<Object>*load(string name);

        void print();
};