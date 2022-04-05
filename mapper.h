#ifndef MAPPER_H
#define MAPPER_H

#include <iostream>
#include <fstream>
#include "rplidar.h"
#include "position.h"

#define OFFSET 1.0

class Mapper
{

public:
    Mapper();
    void processData(Position &robot, LaserMeasurement data);
    void generateMap();
private:
    double x,y;
    int x_index,y_index;
    int map[300][300];
    std::ofstream myfile;

};

#endif // MAPPER_H
