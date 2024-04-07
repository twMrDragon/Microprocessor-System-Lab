#include "triangle.h"
#include "shape.h"
#include "ellipse.h"
#include "circular_sector.h"
#include "sort.h"
#include <iostream>
#include <vector>
int main()
{
  std::vector<Shape*> shapes({new Ellipse(4.0,5.0), new CircularSector(10,90) ,new CircularSector(10,60), new Triangle(0,0,10,0,10,10)});
  std::cout << "原本的: ";
  for(std::vector<Shape*>::iterator it=shapes.begin();it!=shapes.end();it++)
  {
    std::cout << (*it)->area() << ' ';
  }
  sortByArea(shapes.begin(),shapes.end());
  std::cout << "\n排序後: ";
  for(std::vector<Shape*>::iterator it=shapes.begin();it!=shapes.end();it++)
  {
    std::cout << (*it)->area() << ' ';
  }
  std::cout << "\n作業一完成\n";
}
