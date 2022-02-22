#ifndef POSITION_H
#define POSITION_H
#include "ckobuki.h"


        struct Coords{
            double x;
            double y;
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
          double wheel_base = 0.20;
//        double wheel_radius = 0.035;
        static constexpr double TICK= 0.000085292090497737556558;

 // Definicia premennych
       int l;         //Vzdialenost
       int l_r;       //Prejdena vzdialenost praveho kolesa
       int l_l;       //Prejdena vzdialenost laveho kolesa
       RobotPosition pos;

 // Prototypy funkcií
        Position();
        Coords getPosition(void);
        double getRotation(void);
        void processData(TKobukiData data);
        void setX(double x);
        void setY(double y);
        void setFi(double fi);
        double getDistanceR();
        double getDistanceL();
};

#endif // POSITION_H
