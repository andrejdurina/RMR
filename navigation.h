#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <qobject.h>
#include "position.h"
#define UPPER_LIMIT ( 4 * M_PI/180 )
#define LOWER_LIMIT ( 0.5 * M_PI/180 )
class Navigation : public QObject
{
    Q_OBJECT

public:
    Navigation(QObject *parent = nullptr);
    double clcDeviation(Coords start, Coords end);
    void processData(Position& robotHandler);
    void Controller();
    bool nav_active = false;
    void deleteWayPoint(int index);
    void addWayPointFront(string waypoint);
    void addWayPointBack(string waypoint);
    bool IsRobotRotating();
    deque<Coords> waypoints;
private:
    double err_distance,err_rotation,rotation;
    double rotation_speed;
    double translation_speed;
    Coords coords{0,0};
    bool rotate_robot ;
    int rampTranslate(int speed);
    double rampRotate(double speed);
    int prev_tr_speed = 0;
    double prev_rt_speed = 0;

signals:
   void setTranslationSpeed(int speed);
   void setRotationSpeed(double rotation);
   void deleteWaypointGUI(int index);

};

#endif // NAVIGATION_H
