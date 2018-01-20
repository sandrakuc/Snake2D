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
        list<Point> getWallPoints();

        /**
        * porusza snejkiem o wczesniej zadany kierunek. Jakby jedna klatka fps
        * @return jeœli false, to koniec gry. gracz wszedl w jakas przeszkode
        */
        bool tick();


        void setDirection(Direction dir);
        Point food;
    protected:

    private:
        Point head;
        enum Direction direction;
        list<Point> tail;

        list<Point> wall;

        bool checkApple();

        /**
        * porusza snejkiem o jedna kratke
        */
        void move();
        void moveHead();
        void randFood();
        bool checkCollision();
};

#endif // SNAKEENGINE_H
