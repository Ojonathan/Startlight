#include "dest.h"

#include<QBrush>
#include<QPixmap>

Dest::Dest(const Point & p, int e) :objectStar("DESTINATION"), pos {p}, edge {e}
{
    //verifier p
    if(pos.getX() < 0) pos.setX(abs(pos.getX()));
    if(pos.getY() < 0) pos.setY(abs(pos.getY()));

    //verifier edge
    if(edge == 0){
        edge = 10;
    }else if(edge < 0){
        edge = abs(edge);
    }
    this->setBrush(Qt::yellow);
    this->setRect(pos.getX(),pos.getY(),edge,edge);
}

const Point & Dest::getPosition() const
{
    return pos;
}

int Dest::getEdge() const
{
    return edge;
}

bool Dest::isLightedUp() const
{
    return light;
}

void Dest::setLightedUp(const bool q)
{
    light = q;
}

Ray * Dest::strike(Ray *& ray, Point p){
    setLightedUp(true);
    ray->setEnd(p);
    return nullptr;
}

std::ostream & operator<<(std::ostream & out, const Dest & d)
{
    out << "Dest --- Position : " << d.pos <<  " , Edge : " << d.edge <<
        " , lighted up : " << d.light;
    return out;
}
