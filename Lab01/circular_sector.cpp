#include <math.h>
#include"circular_sector.h"
#include <sstream>
using namespace std;
CircularSector::CircularSector(double radius, double degree): _radius(radius), _degree(degree){}
double CircularSector::area() const
{
  return _radius*_radius*M_PI*(_degree/360);
}
double CircularSector::perimeter() const
{
  return 2*_radius*M_PI*(_degree/360)+2*_radius;
}
double CircularSector::sumOfSquares() const
{
  return pow(area(),2)+pow(perimeter(),2);
}
