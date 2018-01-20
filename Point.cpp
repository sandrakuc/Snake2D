#include "Point.h"

Point::Point()
{

}

Point::Point(int xParam, int yParam)
{
    x = xParam;
    y = yParam;
}

void Point::setX(int xParam)
{
    this->x = xParam;
}

void Point::setY(int yParam)
{
    this->y = yParam;
}

double Point::getConvertedX()
{
    return x*0.1-3;

}
double Point::getConvertedZ()
{
    return y*0.1-2;
}

Point::~Point()
{
    //dtor
}
