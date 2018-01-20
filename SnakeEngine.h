#ifndef SNAKEENGINE_H
#define SNAKEENGINE_H

#include "Point.h"
#include <list>
#include <iostream>
#include <cstddef>

using namespace std;



class SnakeEngine
{
    public:
        enum Direction
        {
            LEFT, RIGHT, UP, DOWN
        };
        SnakeEngine();
        virtual ~SnakeEngine();
        list<Point> getSnakePoints();

        void move();


        void setDirection(Direction dir);
        Point food;
    protected:
        Point head;
        enum Direction direction;
        list<Point> tail;


    private:
};

#endif // SNAKEENGINE_H
