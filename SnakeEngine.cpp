#include "SnakeEngine.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

#define WIDTH 60
#define HEIGHT 20

SnakeEngine::SnakeEngine()
{
    food = Point(50,10);

    direction = SnakeEngine::RIGHT;
    head.x = 10;
    head.y = 10;

    tail.push_back(Point(10,11));
    tail.push_back(Point(10,12));

    //generowanie walla
    for(int i =0; i<HEIGHT; i++) {
        wall.push_back(Point(0,i));
    }

    for(int i =0; i<HEIGHT; i++) {
        wall.push_back(Point(WIDTH,i));
    }

    for(int i =0; i<WIDTH; i++) {
        wall.push_back(Point(i,0));
    }

    for(int i =0; i<=WIDTH; i++) {
        wall.push_back(Point(i,HEIGHT));
    }
}

bool SnakeEngine::tick()
{
    bool checkCollisionResult = checkCollision();

    bool checkAppleResult = checkApple();

    if(!checkAppleResult) {
        move();
    }
    return !checkCollisionResult;
}

void SnakeEngine::moveHead()
{
    if(direction == LEFT) {
        head.x--;
    }
    if(direction == RIGHT) {
        head.x++;
    }
    if(direction == UP) {
        head.y--;
    }
    if(direction == DOWN) {
        head.y++;
    }

}

void SnakeEngine::move()
{
    int lastX = head.x;
    int lastY = head.y;

    moveHead();


    int tmpX;
    int tmpY;

    for(Point& p : tail) {

        tmpX = p.x;
        tmpY = p.y;

        p.setX(lastX);
        p.setY(lastY);

        lastX = tmpX;
        lastY = tmpY;

    }

}

bool SnakeEngine::checkApple() {
    if(head.x == food.x && head.y == food.y) {

        //porusza siê sama g³owa, a na jej miejsce wstawiamy nowy element
        tail.push_front( Point(head.x, head.y) );
        moveHead();

        randFood();
        //@todo punkty
        return true;
    }
    return false;
}

void SnakeEngine::setDirection(Direction dir)
{
    this->direction = dir;
}


list<Point> SnakeEngine::getSnakePoints() {
    list<Point> ret;
    ret.push_back(head);

    for(Point p : tail) {
        ret.push_back(p);
    }

    return ret;
}

void SnakeEngine::randFood()
{
    food.x = rand()%(WIDTH-1) +1;
    food.y = rand()%(HEIGHT-1) +1;
}

bool SnakeEngine::checkCollision()
{

    for(Point p : wall) {
        if(head.x == p.x && head.y == p.y) {
            return true;
        }
    }

    for(Point p : tail) {
        if(head.x == p.x && head.y == p.y) {
            return true;
        }
    }



    return false;
}

list<Point> SnakeEngine::getWallPoints()
{
    return wall;
}

SnakeEngine::~SnakeEngine()
{

}
