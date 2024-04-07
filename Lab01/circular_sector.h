#ifndef CIRCULARSECTOR_H
#define CIRCULARSECTOR_H
#include "shape.h"
class CircularSector:public Shape
{
public:
    CircularSector(double radius, double degree);
    double area()const;
    double perimeter()const;
    double sumOfSquares()const;
private:
  double _radius;
  double _degree;
};
#endif
