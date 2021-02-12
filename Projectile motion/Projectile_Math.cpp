#include "Projectile_Math.h"

Projectile_math::Projectile_math()///Empty constructor...just initialises variables
{
    Initialise();
}
Projectile_math::Projectile_math(double Accele,int x_scale_f,int y_scale_f)///Create constructor
{
    Acceleration=Accele;
    X_scale_factor=x_scale_f;
    Y_scale_factor=y_scale_f;

    Current_Y_distance=NULL;
    Current_X_distance=NULL;
    Current_Acceleration=NULL;
}

Projectile_math::~Projectile_math()///Destructor
{
    delete this;
}

void Projectile_math::Initialise()
{
    Acceleration=9.81;      /// In Cape Town (South Africa)
    Time=NULL;              ///

    Current_Y_distance=NULL;
    Current_X_distance=NULL;
    Current_Acceleration=NULL;
}

double Projectile_math::DegreesToRad(double Degrees)
{
    return ((Degrees*pi)/180);
}

double Projectile_math::RadToDegrees(double Radians)
{
    return ((180*Radians)/pi);
}

double Projectile_math::KpHToMpS(double KilometersPerHour)
{
    return KilometersPerHour*0.27;
}

double Projectile_math::X_distance(double time,double angle_Rad,double Initial_Velocity)
{
    Time=time;
    Init_Velocity=Initial_Velocity;
    angle=RadToDegrees(angle_Rad);
    Current_X_distance=(Initial_Velocity*cos(angle_Rad)*time);
    return Current_X_distance;
}

double Projectile_math::Y_distance(double time,double angle_Rad,double Initial_Velocity)
{
    Time=time;
    Init_Velocity=Initial_Velocity;
    angle=RadToDegrees(angle_Rad);
    Current_Y_distance=((Initial_Velocity*sin(angle_Rad)*time)+(0.5*Acceleration*squared(time)));
    return Current_Y_distance;
}

wxInt16 Projectile_math::X_scaled_distance(double X_distance_in_meters,int max_horizontal)
{
    return (wxInt16)(X_distance_in_meters*X_scale_factor);
}

wxInt16 Projectile_math::Y_scaled_distance(double Y_distance_in_meters,int max_vertical)///Scale nd invert
{
    int buffer=NULL;
    buffer=(int)Y_distance_in_meters*Y_scale_factor;
    return (wxInt16)((max_vertical*Y_distance_in_meters)-buffer);
}

bool Projectile_math::SetScaleFactor(int x_scale_f,int y_scale_f)///Set scale factor
{
    X_scale_factor=x_scale_f;
    Y_scale_factor=y_scale_f;

    if(X_scale_factor==x_scale_f && Y_scale_factor==y_scale_f)
        return true;
        else
        return false;
}

double Projectile_math::GetCurrentVelocity(void)
{
    Vector Vel;
    Vel.x=Init_Velocity*cos(DegreesToRad(angle));
    Vel.y=(Init_Velocity*sin(DegreesToRad(angle)))+Acceleration*Time;

    return sqrt(squared(Vel.x)+squared(Vel.y));
}

double Projectile_math::GetCurrentAngle(void)
{
    Vector Vel;
    Vel.x=Init_Velocity;
    Vel.y=Init_Velocity+Acceleration*Time;

    return RadToDegrees(tan(Vel.y/Vel.x));
}

double Projectile_math::GetCurrentTime(void)
{
    return Time;
}
double Projectile_math::GetCurrentYDistance(void)
{
    return Current_Y_distance;

}

void Projectile_math::SetCurrentYDistance(double distance)
{
    Current_Y_distance=distance;
    return;
}

double Projectile_math::GetCurrentXDistance(void)
{
    return Current_X_distance;

}
double Projectile_math::GetCurrentAcceleration(void)
{
    return Acceleration;
}
