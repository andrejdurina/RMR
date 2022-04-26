    #ifndef MAPPER_H
#define MAPPER_H

#include <iostream>
#include <fstream>
#include <queue>
#include "rplidar.h"
#include "position.h"

#define OFFSET 1.0
#define VERTICAL_MAP_LIMIT 150
#define HORIZONTAL_MAP_LIMIT 150
class Mapper
{

public:
    Mapper();
    void processData(Position &robot, LaserMeasurement data);
    void saveMap();
    void loadMap();
    void FloodFill(Coords coords,Position &robot);
    void postProcessData();
    Coords_I fromWorldToIndex(Coords coords);
    void saveFloodedMap();
private:
    double x,y;
    int x_index,y_index;
    int map[VERTICAL_MAP_LIMIT][HORIZONTAL_MAP_LIMIT];
    int cpy_map[HORIZONTAL_MAP_LIMIT][VERTICAL_MAP_LIMIT];
    std::ofstream wfile;
    std::ifstream rfile;
};

#endif // MAPPER_H
