#include "point.h"

Point::Point(int a, int b) : x {a}, y {b}
{}

int Point::getX() const
{
    return x;
}

int Point::getY() const
{
    return y;
}

void Point::setX(int a)
{
    x = a;
}

void Point::setY(int a)
{
    y = a;
}

void Point::setLocation(int a, int b)
{
    x = a;
    y = b;
}

std::ostream & operator<<(std::ostream & out, const Point & p)
{
    out << "( " << p.x << " , " << p.y << " )";
    return out;
}
