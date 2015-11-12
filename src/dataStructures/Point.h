#ifndef POINT
#define POINT
class Point{
        
    int offAngles [8];
    int positionRadian, positionHeight, positionDistance;        
    public :
    Point ();
    Point (int , int , int );
    int getArraySlice(void);
    int getDegree(void);
    char getIdentifyingChar(void);
    int getPositionDistance(void);
    void moveUp();
    void moveDown();
    void rotateRight();
    void rotateLeft();
    void moveIn();
    void moveOut();
};
#endif