    #ifndef MAPPER_H
#define MAPPER_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
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
    void generateMap();
    void loadMap();
    void FloodFill();
private:
    double x,y;
    int x_index,y_index;
    int map[VERTICAL_MAP_LIMIT][HORIZONTAL_MAP_LIMIT];
    std::ofstream wfile;
    std::ifstream rfile;
};

#endif // MAPPER_H
