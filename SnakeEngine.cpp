#include "SnakeEngine.h"

using namespace std;

SnakeEngine::SnakeEngine()
{
    direction = SnakeEngine::RIGHT;
    head.x = 10;
    head.y = 10;

    tail.push_back(Point(10,11));
    tail.push_back(Point(10,12));

}
void SnakeEngine::move()
{
    int lastX = head.x;
    int lastY = head.y;

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



SnakeEngine::~SnakeEngine()
{
    //dtor
}
