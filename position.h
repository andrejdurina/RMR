#ifndef POSITION_H
#define POSITION_H
#include "ckobuki.h"
#include "math.h"
#include <string>
#include <iostream>
#include <deque>
#include "QString"
struct Coords{
    double x{0};
    double y{0};
    Coords() = default;
    Coords(double x,double y)
            {
                this->x = x;
                this->y = y;
            };
    bool operator==(const Coords obj)
    {
        return this->x == obj.x && this->y == obj.y;/* your comparison code goes here */
    };

    QString toString()
    {
       return  QString::number(this->x)+ " " + QString::number(this->y);
    };
};

struct Coords_I{
    int x{0};
    int y{0};
    Coords_I() = default;
    Coords_I(int x,int y)
            {
                this->x = x;
                this->y = y;
            };
    bool operator==(const Coords_I obj)
    {
        return this->x == obj.x && this->y == obj.y;/* your comparison code goes here */
    };
};


   // Struktura pozicia a natocenia robota.
struct RobotPosition{
    Coords coord2D{0, 0};  //Pozicia Y
    double fi{0};         //Uhol natocenia
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
       int enc_r;
       int enc_l;
       RobotPosition pos;

 // Prototypy funkcií
        Position();
        void processData(TKobukiData data);
        double AngleLimiter( double &fi);
        // Buffer overflow
        double encoderOverflow (unsigned short previous , unsigned short actual);
        // Control waypoints
        Coords diffCoords(Coords start, Coords end);
        //Setters
        void setPosX(double x);
        void setPosY(double y);
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
