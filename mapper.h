#ifndef MAPPER_H
#define MAPPER_H

#include <iostream>
#include <fstream>
#include "mainwindow.h"
class Mapper
{

public:
    Mapper();
    int** processData(LaserMeasurement data);
    void generateMap(int** map);
private:
    int map[500][500];
    std::ofstream myfile;
};

#endif // MAPPER_H
