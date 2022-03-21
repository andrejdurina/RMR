#include "mapper.h"

Mapper::Mapper()
{

}

int** Mapper::processData(LaserMeasurement data)
{ //  if(data.numberOfScans...)

}
void Mapper::generateMap(int** map)
{
    myfile.open("map");
    myfile << map;
    myfile.close();
}
