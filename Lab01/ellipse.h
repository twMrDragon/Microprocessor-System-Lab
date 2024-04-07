#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"
class Ellipse:public Shape
{
public:
    Ellipse(double semiMajorAxes,double semiMinorAxes);
    double area() const;
    double perimeter() const;
    double sumOfSquares() const;
private:
  double _semiMajorAxes;
  double _semiMinorAxes;
};
#endif
