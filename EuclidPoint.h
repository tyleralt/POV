#ifndef EUCLID
#define EUCLID
#include "Point.h"
class EuclidPoint{

    public:
    int getSecondCrossingDegree (int , int);
    int getFirstCrossingDegree (int , int);
    int x, y , z;
    EuclidPoint(int, int, int);
    EuclidPoint(void);
    Point getStartPoint();
    Point getEndPoint();
    Point getPoint();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveTowards();
    void moveAway();
    
};
#endif