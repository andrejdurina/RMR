#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <qobject.h>
#include "position.h"
#define UPPER_LIMIT ( 2*M_PI/180 )
#define LOWER_LIMIT ( M_PI/180/2 )
class Navigation : public QObject
{
    Q_OBJECT

public:
    Navigation(QObject *parent = nullptr);
    double clcDeviation(Coords start, Coords end);
    void processData(Position& robotHandler);
    void Controller();
    bool nav_active = false;
private:
    double err_distance,err_rotation,rotation;
    double rotation_speed;
    double translation_speed;
    Coords coords{0,0};
    bool rotate_robot = true,translate_robot = false;
signals:
   void setTranslationSpeed(int speed);
   void setRotationSpeed(double rotation);

};

#endif // NAVIGATION_H
