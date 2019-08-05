#include "lens.h"

#include <QPen>

Lens::Lens(const Point & p, int w, int h, int min, int max) : objectStar("LENS"),pos {p},
    width {w}, height {h}, wlmin {min}, wlmax {max}
{
    //verifier pos
    if(pos.getX() < 0) pos.setX(abs(pos.getX()));
    if(pos.getY() < 0) pos.setY(abs(pos.getY()));

    //si les valeur sont negatifs
    if(width < 0 || height < 0){
        width = abs(width);
        height = abs(height);
    }

    if(width == 0){
        width = 10;
    }
    if(height == 0){
        height = 10;
    }

    if(wlmin > wlmax){
        int aux = wlmax;
        wlmax = wlmin;
        wlmin = aux;
    }

    this->setRect(pos.getX(),pos.getY(),width,height);
}

void Lens::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen(Qt::cyan, 2);
    QPointF center(pos.getX() + width /2,pos.getY() + height /2);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    //QPainterPath path;
    //path.addEllipse(center,width/2,height/2);

    //QPainterPathStroker spath;
    //QPainterPath insidePath;
    //QPainterPath outlinePath(spath.createStroke(path));

    //QPainterPath path;
    //insidePath = path.intersected(path);
    //painter->strokePath(outlinePath,pen);
    //painter->drawPath(insidePath);
    painter->drawEllipse(center,width/2,height/2);
}

const Point & Lens::getPosition() const
{
    return pos;
}

int Lens::getWidth() const
{
    return width;
}

int Lens::getHeight() const
{
    return height;
}

int Lens::getMinWavelength() const
{
    return wlmin;
}

int Lens::getMaxWavelength() const
{
    return wlmax;
}

Ray * Lens::strike(Ray *& ray, Point p){
    if(ray->getWavelength() < wlmin || ray->getWavelength() > wlmax){
        ray->setEnd(p);
        return nullptr;
    }
    ray->setEnd(p);
    return new Ray(p2ellipse,ray->getAngle(),ray->getWavelength());
}

void Lens::setP2ellipse(const Point value)
{
    p2ellipse = value;
}

std::ostream & operator<<(std::ostream & out, const Lens & l)
{
    out << "Lens -- Position : " << l.pos << " , width : " << l.width
        << " , height : " << l.height << " , Freq. Min. : " << l.wlmin <<
        " , Freq. Max. : " << l.wlmax;
    return out;
}
