#include <fstream>
#include <string>
#include <vector>

#ifndef FILE
    #define FILE
    #include "file.h"
#endif

#ifndef NODE
    #define NODE
    #include "node.h"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "quadtree.h"
#endif

#ifndef ELEMENT
    #define ELEMENT
    #include "element.h"
#endif

using namespace std;

namespace colour{
    class bnw: public element{

        public:
            bnw();
            bnw(string status);

            void setStatus(string status);
            string getStatus() const;

            bool operator== (const bnw &bnw) const;

            void validate(string argc);
            void print();

            static quadtree<bnw>*parse(unsigned l, unsigned chars, ifstream &name);
            static bnw parseLine(string line);
    };
}
