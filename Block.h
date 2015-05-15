#ifndef BLOCK
#define BLOCK
class Block{
    public :
    int x, y, z;     
    int size, height;   
    Block (int, int, int, int, int);
     Block ();
    void moveRight();
    void moveLeft();
    void moveIn();
    void moveOut();
};
#endif