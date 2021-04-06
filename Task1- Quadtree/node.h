template <class Object>
class node{

    private:
        unsigned x;
        unsigned y;
        Object status;

    public:
        node();
        node(unsigned x, unsigned y, Object status);

        unsigned getX();
        void setX(unsigned x);
        unsigned getY();
        void setY(unsigned y);
        unsigned getStatus();
        Object setStatus(unsigned status);

        void print();
};