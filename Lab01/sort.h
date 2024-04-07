#ifndef SORT_H
#define SORT_H
#include <vector>
#include "shape.h"
void sortByArea(std::vector<Shape*>::iterator front,std::vector<Shape*>::iterator end);
bool areaAscendingComparison(Shape *a, Shape *b);
#endif
