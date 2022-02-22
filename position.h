#ifndef POSITION_H
#define POSITION_H
#include "ckobuki.h"
#include "math.h"

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
       int enc_r;
       int enc_l;
       RobotPosition pos;

 // Prototypy funkcií
        Position();
        void processData(TKobukiData data);
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
        int getEncR();
        int getEncL();
        double getPosX();
        double getPosY();
};

#endif // POSITION_H
