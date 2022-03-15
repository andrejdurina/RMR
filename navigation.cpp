#include "navigation.h"

Navigation::Navigation(QObject *parent):
    QObject(parent)
{

}

double Navigation::clcDeviation(Coords start, Coords end)
{
    double result;
    result = sqrt(pow(end.x-start.x,2) + pow(end.y-start.y,2));
    return result;
}


void Navigation::processData(Position& robotHandler)
{
    if(!nav_active){
        return;
    }
    if(robotHandler.waypoints.size() > 0){
        err_distance = clcDeviation(robotHandler.getPosition(),robotHandler.waypoints.front());
        coords = robotHandler.diffCoords(robotHandler.getPosition(),robotHandler.waypoints.front());
        rotation = atan2(coords.y,coords.x);
        err_rotation = robotHandler.getRotation() - rotation;
        std::cout<<"rot err: "<<err_rotation<<" dist err: "<<err_distance<<std::endl;
        robotHandler.AngleLimiter(err_rotation);

        rotation_speed =    err_rotation * 5 ;
        translation_speed = err_distance * 1000;


        if(translation_speed > 300)
        {
            translation_speed = 300;
        }

        if(rotation_speed > M_PI/4)
        {
            rotation_speed = M_PI/4;
        }
       if(rotation_speed < -M_PI/4)
       {
           rotation_speed = -M_PI/4;
       }

        Controller();


    //Robot dojde na bod , over ho , vymaz bod z decku. continue
        if (err_distance < 0.001)
        {
            robotHandler.waypoints.pop_front();
            emit setTranslationSpeed(0);
        }
    }

}

//bool turning;
//const double hyst_low = 1 * pi/180;
//const double hyst_high = 5 * pi/180;
//...

//if(turning && (angle_error < hyst_low))
//{
//    turning = false;
//}
//if(!turning && (angle_error > hyst_high)
//{
//    turning = true;
//}

//if(turning) doTurnStuff();
//else doTranslationStuff();

void Navigation::Controller()
{
//    if(abs(err_rotation) > UPPER_LIMIT){
//        rotate_robot = true;
//    }
//    if(abs(err_rotation) < LOWER_LIMIT){
//        rotate_robot = false;
//    }

    if(rotate_robot) //(err_rotation > 0.02 || err_rotation < - 0.02)
    {
        emit setRotationSpeed(rotation_speed);
        std::cout<<"rotating"<<std::endl;
    }
    else
    {   emit setTranslationSpeed(translation_speed);
        std::cout<<"translating"<<std::endl;
    }
}
