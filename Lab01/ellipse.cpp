#include "ellipse.h"
#include <math.h>
#include <sstream>
using namespace std;
Ellipse::Ellipse(double semiMajorAxes,double semiMinorAxes): _semiMajorAxes(semiMajorAxes), _semiMinorAxes(semiMinorAxes)
{
  if(semiMajorAxes<semiMinorAxes)
  {
    _semiMajorAxes=semiMinorAxes;
    _semiMinorAxes=semiMajorAxes;
  }
}
double Ellipse::area() const
{
  return M_PI*_semiMajorAxes*_semiMinorAxes;
}
double Ellipse::perimeter() const
{
  return 2*M_PI* _semiMinorAxes + 4*(_semiMajorAxes-_semiMinorAxes);
}
double Ellipse::sumOfSquares() const
{
  return pow(area(),2)+pow(perimeter(),2);
}
