#include "objectStar.h"
#include "wall.h"
#include <QPen>

Wall::Wall(const Point & p1, const Point & p2) : objectStar("WALL"),start{p1},end{p2}
{
    if(start.getX() == end.getX() && start.getY() == end.getY()){
        end.setLocation(start.getX() + 20,start.getY() + 20);
    }

    QPen pen(Qt::black, 5);
    this->setPen(pen);
    this->setLine(start.getX(),start.getY(),end.getX(),end.getY());
}

const Point & Wall::getStart() const
{
    return start;
}

const Point & Wall::getEnd() const
{
    return end;
}

Ray * Wall::strike(Ray *& ray, Point p){
    ray->setEnd(p);
    return nullptr;
}

std::ostream & operator<<(std::ostream & out, const Wall & w)
{
    out << "Wall --- Start : "  << w.start << ", End : " << w.end;
    return out;
}
