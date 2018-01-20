#include "SnakeEngine.h"

using namespace std;

SnakeEngine::SnakeEngine()
{
    direction = SnakeEngine::DOWN;
    head.x = 10;
    head.y = 10;

    tail.push_back(Point(10,11));
    tail.push_back(Point(10,12));

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
