#include "nuke.h"
#include<QBrush>
#include<QPixmap>

Nuke::Nuke(const Point & p, int r) : objectStar("NUKE"),pos {p}, rad {r}
{
    //verifier pos
    if(pos.getX() < 0) pos.setX(abs(pos.getX()));
    if(pos.getY() < 0) pos.setY(abs(pos.getY()));

    //verifier rad
    if(rad == 0){
        rad = 10;
    }else if(rad < 0){
        rad = abs(rad);
    }
    //desiner la bombe.
    light = false;
    this->setRect(pos.getX() - rad ,pos.getY() - rad ,rad * 2,rad * 2);
}

const Point &Nuke::getLocation() const
{
    return pos;
}

int Nuke::getRadius() const
{
    return rad;
}

bool Nuke::isLightedUp() const
{
    return light;
}

void Nuke::setLightedUp(bool q)
{
    light = q;
}

Ray * Nuke::strike(Ray *& ray, Point p){
    ray->setEnd(p);
    setLightedUp(true);
    return nullptr;
}

void Nuke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPointF center(pos.getX(),pos.getY());

    /*QRadialGradient radial;
    radial.setCenter(pos.getX(),pos.getY());
    radial.setFocalPoint(rad,rad);
    radial.setRadius(rad);
    radial.setColorAt(1.0, Qt::cyan);
    radial.setColorAt(0.5, Qt::yellow);
    */

    //QPen pen;
    //pen.setc
    //pen.setBrush(radial);

    painter->setRenderHint(QPainter::Antialiasing);
    //painter->setPen(pen);
    //painter->setCompositionMode(QPainter::CompositionMode_Source);
    //painter->setBrush(radial);
    painter->setBrush(Qt::red);
    painter->drawEllipse(center,rad,rad);
}

std::ostream & operator<<(std::ostream & out, const Nuke & s)
{
    out << "Nuke --- Position : " << s.pos << " , Radius : " << s.rad <<
        " On : " << s.light;
    return out;
}
