#include "navigation.h"

Navigation::Navigation(QObject *parent):
    QObject(parent)
{

}

bool Navigation::IsRobotRotating()
{
    return rotate_robot;
}

double Navigation::clcDeviation(Coords start, Coords end)
{    double result,x,y;

     x = end.x-start.x;
     y = end.y-start.y ;

    result = sqrt(pow(x,2) + pow(y,2));
    return result;
}


void Navigation::processData(Position& robotHandler)
{
    if(!nav_active){
        return;
    }
    if(waypoints.size() > 0){
        std::cout << "Current waypoint: X: " << waypoints.front().x <<
                     ", Y: " << waypoints.front().y << std::endl;

        err_distance = clcDeviation(robotHandler.getPosition(),waypoints.front());

        coords = robotHandler.diffCoords(robotHandler.getPosition(),waypoints.front());
        rotation = atan2(coords.y,coords.x);

        err_rotation = rotation - robotHandler.getRotation();// - rotation;
        robotHandler.AngleLimiter(err_rotation);
        std::cout<<"rot err: "<<err_rotation<<"| dist err: "<<err_distance<<std::endl;


        rotation_speed =    err_rotation * 10 ;
        translation_speed = err_distance * 2500;

        std::cout<< "Deque contents:" << std::endl;
        for(auto& wp : waypoints)
        {
            std::cout << "X: " << wp.x << ", Y: " << wp.y << std::endl;
        }
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
        if (err_distance < 0.009)
        {
            emit setTranslationSpeed(0);
            deleteWayPoint(0);
        }
    }
    else
    {
        nav_active = false;
    }

}




void Navigation::Controller()
{
    if(rotate_robot && (abs(err_rotation) < LOWER_LIMIT))
    {
        rotate_robot = false;
    }
    if((abs(err_rotation) > UPPER_LIMIT))
    {
        rotate_robot = true;

    }
    if(rotate_robot)
    {
        prev_tr_speed = 0;
        rotation_speed = rampRotate(rotation_speed);
        emit setRotationSpeed(rotation_speed);
        prev_rt_speed = rotation_speed;
        std::cout<<"rotating "<<rotation_speed<<" rad/s"<<std::endl;
    }
    else
    {
        prev_rt_speed = 0;
        translation_speed = rampTranslate(translation_speed);
        emit setTranslationSpeed(translation_speed);
        prev_tr_speed = translation_speed;
        std::cout<<"translating "<<translation_speed<<" mm/s"<<std::endl;
    }
}

void Navigation::addWayPointBack(string waypoint)
{

    this->waypoints.push_back(parseInput(waypoint));
};

void Navigation::addWayPointBack(Coords waypoint)
{
    this->waypoints.push_back(waypoint);
};

void Navigation::addWayPointFront(string waypoint)
{
    this->waypoints.push_front(parseInput(waypoint));
};

void Navigation::deleteWayPoint(int index)
{
    this->waypoints.erase(waypoints.begin()+index);
    emit deleteWaypointGUI(index);
};

int Navigation::rampTranslate(int speed)
{

    if((speed - prev_tr_speed) > 20)
    {
        return prev_tr_speed+20;
    }
    else return speed;

}
double Navigation::rampRotate(double speed)
{
    if(speed - prev_rt_speed > M_PI/180*3)
    {
        return prev_rt_speed+M_PI/180*3;
    }
    if(speed - prev_rt_speed < -M_PI/180*3)
    {
        return prev_rt_speed-M_PI/180*3;
    }
    else return speed;
}

Coords Navigation::parseInput(string waypoint)
{
    int index;
    string X,Y;
    index = waypoint.find(' ');


    X = waypoint.substr(0,index);
    Y = waypoint.substr(index,string::npos);

    double x = std::stod(X);
    double y = std::stod(Y);
    return Coords(x,y);
}

