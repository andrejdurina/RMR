#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "position.h"

class Navigation
{
public:
    Navigation();
    void setCourse();
    double clcDeviation(Coords start, Coords end);
};

#endif // NAVIGATION_H
