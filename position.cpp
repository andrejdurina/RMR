#include "position.h"

Position::Position()
{
    l_r = -1;
    l_l = -1;

};


void Position::processData(TKobukiData data){
    // Check 1st time encoder values could be rng.
     if(l_r == -1 && l == -1)
        {
           l_r = data.EncoderRight;
           l_l = data.EncoderLeft;
        }
    else
        {//Position of robot.
          pos.coord2D.x = TICK * (data.EncoderRight - getDistanceR());
          pos.coord2D.y = TICK * (data.EncoderLeft - getDistanceL());
          l_r = data.EncoderRight;
          l_l = data.EncoderLeft;
        }

        //Rotation of robot.
      pos.fi = l_r - l_l / wheel_base;

       //Encoder overflow.
      if(data.EncoderRight >= 65534)
      {
          //l_r = 0;

      };

      if(data.EncoderLeft >= 65534)
      {
         // l_l = 0;
      };

};



Coords Position::getPosition(void)
{
//    unsigned short timestamp = data.timestamp;
//    unsigned short right = data.EncoderRight;
//    unsigned short left =  data.EncoderLeft;
//    signed short gyroRotation = ; gyroangle/100

    //Encoders overflow!! 65 535
    //Encoder initial position value!!

    return pos.coord2D;
};

double Position::getRotation(void)
{
    return pos.fi;
};

void Position::setX(double x)
{
    pos.coord2D.x = x;
}

void Position::setY(double y)
{
    pos.coord2D.y = y;
}

void Position::setFi(double fi)
{
    pos.fi = fi;
}

double Position::getDistanceR()
{
    return l_r;
}

double Position::getDistanceL()
{
    return l_l;
}
