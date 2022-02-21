#ifndef POSITION_H
#define POSITION_H
#include "ckobuki.h"

class Position
{

    public:
 // Vzdialenost medzi kolesami a polomer kolesa
 // Zdroj: http://yujinrobot.github.io/kobuki/enAppendixKobukiParameters.html?fbclid=IwAR1QU70qMPXtuFiY9FCHvbtb-zX5Na7foI5tYPjYYyp63epQWRcFwRYgjJA
        double wheel_base = 0.20;
        double wheel_radius = 0.070;
 // Definicia premennych
        Position();
        static double getPosition(TKobukiData data);

};

#endif // POSITION_H
