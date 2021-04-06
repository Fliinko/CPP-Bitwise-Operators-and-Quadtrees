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
    class boolean: public element{
        public:
            boolean();
            boolean(string status);

            void setStatus(string status);
            bool getBool() const;
            string getStatus() const;

            bool operator== (const boolean &boolean) const;

            void validate(string argc);
            void print();

            static quadtree<boolean>*parse(unsigned l, unsigned chars, ifstream &filename);
            static boolean parseLine(string line);
    };
}