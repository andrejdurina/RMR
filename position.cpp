#include "position.h"


Position::Position()
{
        // Initialize everything to some values.
    setX(0);
    setY(0);
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
          this->l_l = (TICK * encoderOverflow(getEncL(),data.EncoderLeft));//(double)(data.EncoderLeft - getEncL()));
          this->l_r = (TICK * encoderOverflow(getEncR(),data.EncoderRight));//(encoderOverflow(getEncR(),data.EncoderRight)));

          l = (l_l + l_r)/2;

          pos.coord2D.x = getPosX() + l*cos(getRotation());
          pos.coord2D.y = getPosY() + l*sin(getRotation());
          pos.fi = getRotation() + (((l_r - l_l) / wheel_base) );

          setEncR(data.EncoderRight);
          setEncL(data.EncoderLeft);
        }
};

//Encoder overflow. 65 535
// Actual   --> Actual data from encoder.
// Previous --> Previous data from encoder.
double Position::encoderOverflow(unsigned short previous , unsigned short actual)
{
        if((previous - SHRT_MAX  > actual) && (previous > actual))
        {
            return actual - previous + USHRT_MAX;

        }
        else if ((previous - SHRT_MIN  < actual) && (previous < actual))
        {
            return actual - previous - USHRT_MAX ;
        }
        else
            return actual - previous;
};

void Position::addWayPointEnd(string position)
{
    int index;
    string X,Y;
    index = position.find(' ');

    X = position.substr(0,index);
    Y = position.substr(index,string::npos);

    double x = std::stod(X);
    double y = std::stod(Y);
    this->waypoints.push_back(Coords(x,y));
};

void Position::addWayPointStart(string position)
{
    int index;
    string X,Y;
    index = position.find(' ');

    X = position.substr(0,index);
    Y = position.substr(index,string::npos);

    double x = std::stod(X);
    double y = std::stod(Y);
   // this->waypoints.insert(waypoints.begin(),Coords(x,y));
};

void Position::deleteWayPoint(int index)
{
    //this->waypoints.pop_back(Coords(x,y));
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

unsigned short Position::getEncR()
{
    return enc_r;
}
unsigned short Position::getEncL()
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
