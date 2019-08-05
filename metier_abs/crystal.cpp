#include "crystal.h"

#include <QBrush>
#include <QPen>
#include <QPixmap>

Crystal::Crystal(const Point & p, double r, int m) : objectStar("CRYSTAL"),center {p}, rad {r},mod {m}
{
    //verifier p
    if(center.getX() < 0) center.setX(abs(center.getX()));
    if(center.getY() < 0) center.setY(abs(center.getY()));

    //verifier rad
    if(rad == 0){
        rad = 10;
    }else if(rad < 0){
        rad = abs(rad);
    }
    this->setRect(center.getX() - rad ,center.getY() - rad ,rad * 2,rad * 2);
}

const Point & Crystal::getCenter() const
{
    return center;
}

int Crystal::getModifier() const
{
    return mod;
}

double Crystal::getRadius() const
{
    return rad;
}

Ray * Crystal::strike(Ray *& ray, Point p){
    ray->setEnd(p);

    return new Ray(p2circle,ray->getAngle(),ray->getWavelength() + mod);
    //return nullptr;
}

void Crystal::setP2circle(const Point value)
{
    p2circle = value;
}


void Crystal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(QPainter::Antialiasing);
    QPointF center(this->center.getX(),this->center.getY());
    painter->setBrush(Qt::gray);
    painter->drawEllipse(center,rad,rad);
}

std::ostream & operator<<(std::ostream & out, const Crystal & c)
{
    out << "Crystal --- Center : " << c.center << " , Radius : " << c.rad
        << " , Modifier : " << c.mod;
    return out;
}
