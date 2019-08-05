#include "source.h"

#include <QBrush>
#include <QPixmap>
#include <QCursor>

Source::Source(const Point & p, int e, double a, int wl) : pos {p},
alpha {a}, edge {e}, wavelength {wl}
{
    //verifier pos
    if(pos.getX() < 0) pos.setX(abs(pos.getX()));
    if(pos.getY() < 0) pos.setY(abs(pos.getY()));

    //verifier wavelength
    if(wavelength < 360){
        wavelength = 360;
    }else if(wavelength > 830){
        wavelength = 830;
    }

    //verifier edge
    if(edge == 0){
        edge = 10;
    }else if(edge < 0){
        edge = abs(edge);
    }
    setCursor(Qt::PointingHandCursor);
    this->setBrush(Qt::red);
    this->setRect(pos.getX(),pos.getY(),edge,edge);
}

const Point & Source::getPosition() const
{
    return pos;
}

double Source::getAngle() const
{
    return alpha;
}

int Source::getEdge() const
{
    return edge;
}

int Source::getWavelength() const
{
    return wavelength;
}

bool Source::isOn() const
{
    return on;
}

void Source::setOn(bool q)
{
    on = q;
}

//afficher ou pas le rayon
void Source::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!on){
        on = true;
        std::cout<<"On"<<std::endl;
        this->setBrush(Qt::green);

        emit mesOn();
    }else{
        on = false;
        std::cout<<"Off"<<std::endl;
        this->setBrush(Qt::red);

        emit mesOn();
    }
}

std::ostream & operator<<(std::ostream & out, const Source & s)
{
    out << "Source --- Position : " << s.pos << " , Angle : " << s.alpha
        << ", Frequency : " << s.wavelength << " , Edge : " << s.edge <<
        " , on : " <<
        s.on;
    return out;
}
