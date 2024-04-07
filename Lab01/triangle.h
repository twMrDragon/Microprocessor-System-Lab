#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"
class Triangle:public Shape
{
public:
  Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
  bool isIsoscelesTriangle();
  double distance(double x1, double y1, double x2, double y2);
  double area()const;
  double perimeter()const;
  double sumOfSquares()const;
private:
  double _x1;
  double _x2;
  double _x3;
  double _y1;
  double _y2;
  double _y3;
  double d1;
  double d2;
  double d3;
};
#endif
