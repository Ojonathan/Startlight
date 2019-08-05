#include "mirror.h"
#include <cmath>
#include <QPen>
#include <QKeyEvent>
#include <QDebug>
#include <QCursor>
//#include <algorithm>

#define PI (3.141592653589793)

//point,xpad,length,alpha,xmin,ymin,xmax,ymax,alphamin,alphamax
Mirror::Mirror(const Point & p, int x, int len, double a, Point min,Point max, double am, double aM)
    : objectStar("MIRROR"),pivot {p}, length(len), xpad(x), xMin {min.getX()}, xMax {max.getX()},
      yMin {min.getY()}, yMax {max.getY()}, alpha {a}, alphaMin {am},
      alphaMax {aM}
{
    //verifier pivot
    if(pivot.getX() < 0) pivot.setX(abs(pivot.getX()));
    if(pivot.getY() < 0) pivot.setY(abs(pivot.getY()));

    //verifier xMin, xMax, yMin, yMax
    if(xMin < 0) xMin = abs(xMin);
    if(xMax < 0) xMax = abs(xMax);
    if(yMin < 0) yMin = abs(yMin);
    if(yMax < 0) yMax = abs(yMax);

    if(yMax < yMin){
        int aux = yMax;
        yMax = yMin;
        yMin = aux;
    }
    if(xMax < xMin){
        int aux = xMax;
        xMax = xMin;
        xMin = aux;
    }
    if(xMin != xMax || yMin != yMax){
        if(xMin == xMax) xMax = xMax + 25;
        if(yMin == yMax) yMax = yMax + 25;
    }

    //verifier length
    if(length < 0) length = abs(length);
    if(length == 0) length = 58;

    //verifier xpad
    if(xpad < 0) xpad = abs(xpad);
    if(xpad > length) xpad = length;

    m_left = false;
    m_right = false;

    //pour pouvoir toucher avec la souris.
    QPen pen;
    pen.setWidth(8);
    this->setPen(pen);

    setCursor(Qt::OpenHandCursor);
    traceline(pivot);
}

void Mirror::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(QPainter::Antialiasing); //pour eviter la pixelisation.
    QPen pen;
    pen.setWidth(5);

    QPointF p1(start.getX(),start.getY());
    QPointF p2(end.getX(),end.getY());

    Point c((start.getX()+end.getX())/2,(start.getY()+end.getY())/2);
    Point m(c.getX() - (start.getY() - c.getY()),c.getY() - (c.getX() - start.getX()));
    Point n(c.getX() + (c.getY() - end.getY()),c.getY() + (end.getX() - c.getX()));

    //pour donner l'apparence d'un coté reflechisant.
    QLinearGradient lgrad(m.getX(),m.getY(),n.getX(),n.getY());
    lgrad.setColorAt(0.499, Qt::cyan);
    lgrad.setColorAt(0.5, Qt::gray);
    lgrad.setColorAt(0.501, Qt::gray);
    pen.setBrush(lgrad);

    painter->setPen(pen);
    painter->drawLine(p1,p2);

    //revisar.
    QPen point(Qt::red,4);
    painter->setPen(point);
    painter->drawPoint(pivot.getX(),pivot.getY());
}

const Point & Mirror::getPivot() const
{
    return pivot;
}

int Mirror::getLength() const
{
    return length;
}

int Mirror::getXPad() const
{
    return xpad;
}

double Mirror::getAngle() const
{
    return alpha;
}

double Mirror::getMinAngle() const
{
    return alphaMin;
}

double Mirror::getMaxAngle() const
{
    return alphaMax;
}

Point Mirror::getMinPivot() const
{
    return Point {xMin, yMin};
}

Point Mirror::getMaxPivot() const
{
    return Point {xMax, yMax};
}

bool Mirror::setPivot(const Point & p)
{
    bool r {checkPivotRange(p)};
    if (r) pivot = p;
    pivot = p;
    return r;
}

bool Mirror::setAngle(double a)
{
    bool r {checkAngleRange(a)};
    if (r) alpha = a;
    return r;
}

bool Mirror::checkAngleRange(double a) const
{
    return (alphaMin == 0 && alphaMax == 0) ||
           (a >= alphaMin && a <= alphaMax);
}

bool Mirror::checkPivotRange(const Point & p) const
{
    bool res = false;
    if((p.getX() >= xMin && p.getY() >= yMin) && (p.getX() <= xMax && p.getY() <= yMax)){
        res = true;
    }
    return res;
}


//gestion du mirroir au moment de toucher un rayon.
Ray * Mirror::strike(Ray *& ray, Point p){
    bool res = false;
    std::cout<<"angle du rayon recu: _____ "<<ray->getAngle()<<std::endl;
    std::cout<<"angle du mirroir   : _____ "<<alpha<<std::endl;

    double nn;

    if(ray->getAngle() > PI){
        nn = ray->getAngle() - 2*PI;
    }else if (ray->getAngle() < -PI){
        nn = ray->getAngle() + 2*PI;
    }else{
        nn = ray->getAngle();
    }

    std::cout<<"correction du rayon au moment de toucher le mirroir: ____"<<nn<<std::endl;
    if(alpha < 0){
        if(nn > alpha + PI){
            res = true;
        }else if(nn < alpha && nn > PI *-1){
            res = true;
        }
    }
    if(alpha >= 0){
        if(nn < alpha && nn > alpha-PI){
            res = true;
        }
    }

    if(res == true){
        ray->setEnd(p);
        //double newangle = PI * 2 + alpha*2 - ray->getAngle();
        //std::cout<<"nouvelle angle de sortie: "<<alpha*2 - ray->getAngle()<<std::endl;
        double newangle = alpha*2 - nn;//ray->getAngle();
        return new Ray(p,newangle,ray->getWavelength());
    }else{
        ray->setEnd(p);
        return nullptr;
    }
}

Point Mirror::getStart() const
{
    return start;
}

void Mirror::setStart(const Point &value)
{
    start = value;
}

Point Mirror::getEnd() const
{
    return end;
}

void Mirror::setEnd(const Point &value)
{
    end = value;
}

void Mirror::mouseMoveEvent(QGraphicsSceneMouseEvent * event) {
    if(m_left){
        //qDebug()<<event->pos();

        int x = event->pos().x();
        int y = event->pos().y();

        if(checkPivotRange(Point(x,y))){
            pivot.setLocation(x,y);
        }

        this->traceline(pivot);
        emit actionMouse();
        //emit moved();

    }else if(m_right){
        //qDebug()<<event->pos();

        int x = event->pos().x();
        int y = event->pos().y();

        alpha = -1 * atan2(y - pivot.getY(),x - pivot.getX());

        this->traceline(pivot);
        emit actionMouse();
        //emit rotated();
    }
}

void Mirror::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    setCursor(Qt::ClosedHandCursor);
    if(event->button()== Qt::LeftButton){
        m_left = true;
        std::cout<<"click gauche, pret pour me deplacer "<<std::endl;
        emit drawlimit(true,Point(xMin,yMin) ,Point(xMax,yMax));
    } else if(event->button() == Qt::RightButton){
        m_right = true;
        std::cout<<"click droite, pret pour pivoter"<<std::endl;
    }
}


void Mirror::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {
    setCursor(Qt::OpenHandCursor);
    if(event->button()== Qt::LeftButton){
        m_left = false;
        std::cout<<"fini click gauche, le mirroir arrete de se deplacer"<<std::endl;
        emit drawlimit(false,Point(xMin,yMin) ,Point(xMax,yMax));
    } else if(event->button() == Qt::RightButton){
        m_right = false;
        std::cout<<"fini click droite, le mirroir arrete de pivoter"<<std::endl;
    }
}

void Mirror::traceline(Point & p){
    Point pA;
    Point pB;
    //A
    pA.setX(p.getX()-(xpad * cos(alpha)));
    pA.setY(p.getY()+(xpad * sin(alpha)));
    //B
    pB.setX(p.getX()+((length-xpad) * cos(alpha)));
    pB.setY(p.getY()-((length-xpad) * sin(alpha)));

    start = pA;
    end = pB;

    this->setLine(start.getX(),start.getY(),end.getX(),end.getY());
    //this->update();
}

std::ostream & operator<<(std::ostream & out, const Mirror & m)
{
    out << "Mirror --- Pivot : " << m.pivot << " , Length : " << m.length
        << " , x-pad : " << m.xpad << ", Angle : " << m.alpha << " (Deg: " << (m.alpha * 180)/PI << ")"
        " , Angle range : [" << m.alphaMin << "," << m.alphaMax << "]" <<
        "Pivot range : [(" << m.xMin << "," << m.yMin << "),(" << m.xMax <<
        "," << m.yMax << ")]";
    return out;
}
