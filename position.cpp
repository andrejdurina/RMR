#include "position.h"


Position::Position()
{
    setX(0);
    setY(0);
    setFi(0);
    setEncR(-1);
    setEncL(-1);

};


void Position::processData(TKobukiData data){

//    signed short gyroRotation = ; gyroangle/100

        //Encoder overflow. 65 535

    if((getEncL() - SHRT_MAX  > data.EncoderLeft) && getEncL() > data.EncoderLeft)
    {
        //set sumthin left

    }
    else if((getEncR() - SHRT_MAX  > data.EncoderRight) && getEncR() > data.EncoderRight)
    {
        //set sumthin right
    }
    else if (())
    {

    }
    else if (());
    {

    }
   //  Encoder initial position values!!
     if(enc_r == -1 && enc_l == -1)
        {
         setEncR(data.EncoderRight);
         setEncL(data.EncoderLeft);
        }
    else
        {//Position & rotation of robot.
          setEncR(TICK * (double)(data.EncoderRight - getEncR()));
          setEncL(TICK * (double)(data.EncoderLeft - getEncL()));

          l = (l_l + l_r)/2;

          pos.coord2D.x = getPosX() + l*cos(getRotation()/180*M_PI);
          pos.coord2D.y = getPosY() + l*sin(getRotation()/180*M_PI);
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
