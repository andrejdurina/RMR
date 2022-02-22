#include "position.h"


Position::Position()
{
    l_r = -1;
    l_l = -1;
    setX(0);
    setY(0);
    setFi(0);
    setEncR(0);
    setEncL(0);
};


void Position::processData(TKobukiData data){

//    signed short gyroRotation = ; gyroangle/100
        //Encoder overflow. 65 535
//       if(data.EncoderRight >= 65534)
//       {
//           l_r = 0;
//       };

//       if(data.EncoderLeft >= 65534)
//       {
//           l_l = 0;
//       };

    // Encoder initial position values!!
     if(l_r == -1 && l_l == -1)
        {
           l_r = data.EncoderRight;
           l_l = data.EncoderLeft;
        }
    else
        {//Position & rotation of robot.
          l_r = TICK * (data.EncoderRight - getEncR());
          l_l = TICK * (data.EncoderRight - getEncL());

          l = (l_l + l_r)/2;

          pos.coord2D.x = getPosX() + l*cos(getRotation());
          pos.coord2D.y = getPosY() + l*sin(getRotation());
          pos.fi = getRotation() + (((l_r - l_l) / wheel_base) / M_PI * 180);

          setEncR(data.EncoderRight);
          setEncL(data.EncoderLeft);
        }
};



Coords Position::getPosition(void)
{
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

int Position::getDistanceR()
{
    return l_r;
}

int Position::getDistanceL()
{
    return l_l;
}

double Position::getPosX()
{
   return pos.coord2D.x;

}

double Position::getPosY()
{
    return pos.coord2D.y;
}

int Position::getEncR()
{
    return enc_r;
}
int Position::getEncL()
{
    return enc_l;
}
void Position::setEncR(int value)
{
    enc_r = value;
}
void Position::setEncL(int value)
{
    enc_l = value;
}
