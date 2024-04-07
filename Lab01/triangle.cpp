#include <iostream>
#include "triangle.h"
#include <math.h>
#include <string>
using namespace std;
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3): _x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3)
{
  d1 = Triangle::distance(x1,y1,x2,y2);
  d2 = Triangle::distance(x1,y1,x3,y3);
  d3 = Triangle::distance(x2,y2,x3,y3);
  if(!isIsoscelesTriangle())
  {
    throw string("Not a IsoscelesTriangle.");
  }
}
double Triangle::area()const
{
  double s = (d1+d2+d3)/2;
  return sqrt(s*(s-d1)*(s-d2)*(s-d3));
}
double Triangle::perimeter()const
{
  return d1+d2+d3;
}
bool Triangle::isIsoscelesTriangle()
{
  if((fabs(d1-d2)<d3&&d1+d2>d3)||(fabs(d2-d3)<d1&&d3+d2>d1)||(fabs(d1-d3)<d2&&d1+d3>d1))
  {//判斷三角形條件
    if(d1==d2||d1==d3||d3==d2)
    {
      return true;
    }
  }
      return false;
}
double Triangle::distance(double x1, double y1, double x2, double y2)
{
  return  sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
double Triangle::sumOfSquares()const
{
  return pow(area(),2)+pow(perimeter(),2);
}
