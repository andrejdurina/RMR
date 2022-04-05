#include "mapper.h"

Mapper::Mapper()
{
    for(int i = 0; i<300;i++)
        for(int j = 0; j<300;j++)
        {
            map[i][j] = 0;
        }
}

void Mapper::processData(Position &robot, LaserMeasurement data)
{

    for(int i = 0 ; i< data.numberOfScans ; i++)
    {
        if(!(data.Data[i].scanDistance < 0.02)) // Polomer robota ??
        {
            //OFFSET robota vo svete
            x = robot.getPosX() + data.Data[i].scanDistance*0.001 * cos(robot.getRotation() - data.Data[i].scanAngle*(M_PI/180))+OFFSET;
            y = robot.getPosY() + data.Data[i].scanDistance*0.001 * sin(robot.getRotation() - data.Data[i].scanAngle*(M_PI/180))+OFFSET;


            x_index = round(x/0.05); //5x5cm stvorec v mape
            y_index = round(y/0.05); //


            map[x_index][y_index] = 1 ;
        }
    }

}
void Mapper::generateMap()
{
    myfile.open("map");
    for(int i = 0; i<300;i++)
    {
        myfile<< '\n';
        for(int j = 0; j<300;j++)
        {
           myfile <<map[i][j] ;
        }
    }
    myfile.close();
}
