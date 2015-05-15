//#include "Point.h"
#include "EuclidPoint.h"
#include <math.h>

Point EuclidPoint :: getPoint(){
    int degree = (atan2((double)y, (double)x)) * 57.295;
    if (degree < 0){
        degree = 360 + degree;
    }
    double dradius = sqrt((double)(x * x ) + (double)(y * y));
    int radius = rint(dradius) - 2; 
    Point pointer = Point(degree, z, radius);
    return pointer;
}

int EuclidPoint:: getFirstCrossingDegree (int xl, int yl){ // returns the degree of the first cross
   
    double dradius = sqrt((double)(xl * xl ) + (yl * yl));
    int radius = rint(dradius); 
    
    int oneCross = (int)(asin ((double)yl / radius)) * 57.295;
    if (xl < 0 && oneCross > 0){
        oneCross = 180 - oneCross;
    } else if (xl < 0 && oneCross < 0){
        oneCross = 180 - oneCross;
    } else if (xl < 0){
        oneCross = 360 + oneCross;
    }
    
    int twoCross = (int) (acos ((double)xl / radius)) * 57.295;
    if (yl < 0){
        twoCross = 360 - twoCross;
    }  
    if (oneCross < twoCross){
        return twoCross;
    } else {
    return oneCross;
    }
    return 1;
} 

int EuclidPoint :: getSecondCrossingDegree (int xl, int yl){ // returns the degree of the first cross
    double dradius = (sqrt((double)(xl * xl ) + (yl * yl)));
    int radius = rint(dradius); 
    
    int oneCross = (int)(asin ((double)yl / radius)) * 57.295;
    if (xl < 0 && oneCross > 0){
        oneCross = 180 - oneCross;
    } else if (xl < 0 && oneCross < 0){
        oneCross = 180 - oneCross;
    } else if (xl < 0){
        oneCross = 360 + oneCross;
    }
    int twoCross = (int) (acos ((double)xl / radius)) * 57.295;
    if (yl < 0){
        twoCross = 360 - twoCross;
    }
        
    if (oneCross < twoCross){
        return oneCross;
    } else {
        return twoCross;
    }
    return 1;
}



EuclidPoint :: EuclidPoint(void){
    x = 0;
    y = 3;
    z = 4;
}
EuclidPoint :: EuclidPoint(int xi, int yi, int zi){
    x = xi;
    y = yi;
    z = zi;
}

Point EuclidPoint :: getStartPoint(void){
    int degree;
    if (x >= 0 && y >= 0){ //1
        degree = getFirstCrossingDegree(x + 1, y);
    } else if (x < 0 && y >= 0){ //2
        degree = getFirstCrossingDegree(x + 1, y + 1);
    }else if (x < 0 && y < 0){ //3
        degree = getFirstCrossingDegree(x,y+1);
    }else{ //4
        degree = getFirstCrossingDegree(x,y);
    }
    int radius = (int) sqrt((double)(x * x ) + (y * y));
    return Point( degree, z, radius);
}
Point EuclidPoint :: getEndPoint(void){
    int degree;
    if (x >= 0 && y >= 0){ //1
        degree = getFirstCrossingDegree(x, y + 1);
    } else if (x < 0 && y >= 0){ //2
        degree = getFirstCrossingDegree(x , y );
    }else if (x < 0 && y < 0){ //3
        degree = getFirstCrossingDegree(x + 1,y);
    }else{ //4
        degree = getFirstCrossingDegree(x+ 1,y + 1);
    }
    int radius = (int) sqrt((double)(x * x ) + (y * y));
    return Point( degree, z, radius);
}
void EuclidPoint :: moveUp(void){
    z++;
}
void EuclidPoint :: moveDown(void){
    z--;
}
void EuclidPoint :: moveTowards(void){
    y--;
}
void EuclidPoint :: moveAway(void){
    y++;
}
void EuclidPoint :: moveRight(void){
    x++;
}    
void EuclidPoint :: moveLeft(void){
    x--;
}