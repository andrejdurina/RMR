#ifndef POSITION_H
#define POSITION_H
#include "ckobuki.h"
#include "math.h"
#include <string>
#include <iostream>

        struct Coords{
            double x;
            double y;
            Coords(double x,double y)
            {
                this->x = x;
                this->y = y;
            };
        };
            // Struktura pozicia a natocenia robota.
       struct RobotPosition{
           Coords coord2D;  //Pozicia Y
           double fi;  //Uhol natocenia
       };


class Position
{

    public:
 // Vzdialenost medzi kolesami a polomer kolesa
 // Zdroj: http://yujinrobot.github.io/kobuki/enAppendixKobukiParameters.html?fbclid=IwAR1QU70qMPXtuFiY9FCHvbtb-zX5Na7foI5tYPjYYyp63epQWRcFwRYgjJA
          double wheel_base = 0.23;
//        double wheel_radius = 0.035;
          static constexpr double TICK= 0.000085292090497737556558;

 // Definicia premennych
       double l;         //Vzdialenost
       double l_r;       //Prejdena vzdialenost praveho kolesa
       double l_l;       //Prejdena vzdialenost laveho kolesa
       unsigned short enc_r;
       unsigned short enc_l;
       RobotPosition pos;
       vector<Coords> waypoints;

 // Prototypy funkcií
        Position();
        void processData(TKobukiData data);
        // Buffer overflow
        double encoderOverflow (unsigned short previous , unsigned short actual);
        // User waypoints
        void addWayPointEnd(string position);
        void addWayPointStart(string position);
        void deleteWayPoint(string position);
        // Control waypoints

        //Setters
        void setX(double x);
        void setY(double y);
        void setFi(double fi);
        void setEncR(int value);
        void setEncL(int value);

        //Getters
        Coords getPosition(void);
        double getRotation(void);
        int getDistanceR();
        int getDistanceL();
        unsigned short getEncR();
        unsigned short getEncL();
        double getPosX();
        double getPosY();
};

#endif // POSITION_H
