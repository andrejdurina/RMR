#include "navigation.h"

Navigation::Navigation()
{

}

double Navigation::clcDeviation(Coords start, Coords end)
{
    double result;
    result = sqrt(pow(end.x-start.x,2) + pow(end.y-start.y,2));
    return result;
}


