#include "position.h"

Position::Position()
{


};
static double Position::getPosition(TKobukiData data)
{
    unsigned short timestamp = data.timestamp;
    unsigned short right = data.EncoderRight;
    unsigned short left =  data.EncoderLeft;
    signed short gyroRotation = data.GyroAngle;

    //Encoders overflow!!
    //Encoder initial position value!!
     //Position X
        x_1 = x +
     //Position Y
        d_alfa = (l_right - l_left)/d;
     //Rotation

    return 1;
};
