#include "position.h"


Position::Position()
{
        // Initialize everything to some values.
    setPosX(0);
    setPosY(0);
    setFi(0);
    setEncR(-1.0);
    setEncL(-1.0);

};


void Position::processData(TKobukiData data){

   //  Encoder initial position values!!
     if(enc_r == -1.0 && enc_l == -1.0)
     {
         setEncR(data.EncoderRight);
         setEncL(data.EncoderLeft);
     }
    //Calculate position & rotation of robot.
    else
        {
          this->l_l = (TICK * encoderOverflow(getEncL(),data.EncoderLeft));
          this->l_r = (TICK * encoderOverflow(getEncR(),data.EncoderRight));

          l = (l_l + l_r)/2;

          setPosX(getPosX() + l*cos(getRotation()));
          setPosY(getPosY() + l*sin(getRotation()));
          setFi(getRotation() + (((l_r - l_l) / wheel_base) ));

          setEncR(data.EncoderRight);
          setEncL(data.EncoderLeft);
        }
};

//Encoder overflow. 65 535
// Actual   --> Actual data from encoder.
// Previous --> Previous data from encoder.
double Position::encoderOverflow(unsigned short previous , unsigned short actual)
{       //Overflow +
        if((previous - SHRT_MAX  > actual) && (previous > actual))
        {
            return actual - previous + USHRT_MAX;
        }
        //Overflow -
        else if ((previous - SHRT_MIN  < actual) && (previous < actual))
        {
            return actual - previous - USHRT_MAX ;
        }
        else
            return actual - previous;
};

Coords Position::diffCoords(Coords start, Coords end)
{
    Coords result(end.x - start.x,end.y - start.y);
    return result;
};



double Position::AngleLimiter( double &fi)
{
    while(fi > M_PI)
    {
        fi = fi-2*M_PI;
    }
    while(fi < -M_PI)
    {
        fi = fi+2*M_PI;
    }
    return fi;
}


Coords Position::getPosition(void)
{
    return pos.coord2D;
};

double Position::getRotation(void)
{
    return pos.fi;
};

void Position::setPosX(double x)
{
    pos.coord2D.x = x;
}

void Position::setPosY(double y)
{
    pos.coord2D.y = y;
}

void Position::setFi(double fi)
{
    pos.fi = AngleLimiter(fi);
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
