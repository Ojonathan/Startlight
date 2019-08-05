#include "ray.h"
#include<QPen>
#include<Qbrush>
#include<QPixmap>

//réservation des attributs statiques
const int Ray::WL_MIN;
const int Ray::WL_MAX;
const int Ray::WL_DFT;

Ray::Ray(const Point & p1, double newangle ,int wl): start{p1},
angle{newangle},wavelength{wl}
{
    colorRay.setRgb(0,0,0);
    if(wavelength < WL_MIN || wavelength > WL_MAX){
        wavelength = Ray::WL_DFT;
    }
}

Ray::Ray(const Point & p1, const Point & p2,int wl){
    start = p1;
    end = p2;
    wavelength = wl;
    angle = 0.00;

    colorRay = color(wavelength);

    //point central , para hacer el degradé.
    //Point c((a.getX()+b.getX())/2,(a.getY()+b.getY())/2);

    //Point m(c.getX() - (a.getY() - c.getY()),c.getY() - (c.getX() - a.getX()));
    //Point n(c.getX() + (c.getY() - b.getY()),c.getY() + (b.getX() - c.getX()));


    /*QLinearGradient lgrad(m.getX(),m.getY(),n.getX(),n.getY());
    lgrad.setColorAt(0.48, Qt::transparent);
    lgrad.setColorAt(0.494, Qt::red);
    lgrad.setColorAt(0.5, Qt::white);
    lgrad.setColorAt(0.506, Qt::red);
    lgrad.setColorAt(0.52, Qt::transparent);

    pen.setBrush(lgrad);
    */
    //this->setPen(pen);
    this->setLine(start.getX(),start.getY(),end.getX(),end.getY());
}

void Ray::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen;//(Qt::red, 1);

    pen.setColor(colorRay);
    pen.setWidth(1);

    QPointF p1(start.getX(),start.getY());
    QPointF p2(end.getX(),end.getY());

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawLine(p1,p2);
}

QColor Ray::color(int wl){
    QColor c;
    double r,g,b;
    double sss;
    if(wl >= 360 && wl < 440){
        r = -(wl - 440.) / (440. - 350.);
        g = 0.0;
        b = 1.0;
        std::cout<<"1"<<std::endl;
    }else if(wl >= 440 && wl < 490){
        r = 0.0;
        g = -(wl - 440.) / (490. - 440.);
        b = 1.0;
        std::cout<<"2"<<std::endl;
    }else if(wl >= 490 && wl < 510){
        r = 0.0;
        g = 1.0;
        b = -(wl - 510.) / (510. - 490.);
        std::cout<<"3"<<std::endl;
    }else if(wl >= 510 && wl < 580){
        r = (wl - 510.) / (580. - 510.);
        g = 1.0;
        b = 0.0;
        std::cout<<"4"<<std::endl;
    }else if(wl >= 580 && wl < 645){
        r = 1.0;
        g = -(wl - 645.) / (645. - 580.);
        b = 0.0;
        std::cout<<"5"<<std::endl;
    }else if(wl >= 645 && wl < 780){
        r = 1.0;
        g = 0.0;
        b = 0.0;
        std::cout<<"6"<<std::endl;
    }else{
        r = 1.0;
        g = 1.0;
        b = 1.0;
        std::cout<<"0"<<std::endl;
    }

    if(wl >= 380 && wl < 420){
        sss = 0.3 + 0.7 * (wl - 350) / (420 - 350);
    }else if(wl >= 420 && wl <= 700){
        sss = 1.0;
    }else if(wl > 700 && wl <= 780){
        sss = 0.3 + 0.7 * (780 - wl) / (780 - 700);
    }else{
        sss = 1.0;
    }

    sss *= 255;
    c.setRgb((int) (sss * r),(int) (sss * g),(int) (sss*b));
    return c;
}

const Point & Ray::getStart() const
{
    return start;
}

const Point & Ray::getEnd() const
{
    return end;
}

int Ray::getWavelength() const
{
    return wavelength;
}

void Ray::setStart(const Point & p)
{
    start = p;
}

void Ray::setEnd(const Point & p)
{
    end = p;
}

bool Ray::setWavelength(int wl)
{
    bool r = wl >= WL_MIN && wl <= WL_MAX;
    if (r) wavelength = wl;
    return r;
}

double Ray::getAngle() const{
    return angle;
}

void Ray::setAngle(double value){
    angle = value;
}

std::ostream & operator<<(std::ostream & out, const Ray & p)
{
    out << p.start << " ---------- " << p.end << " (" << p.wavelength <<
        " nm)";
    return out;
}
