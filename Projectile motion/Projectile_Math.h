#ifndef PROJECTILE_MATH_H_INCLUDED
#define PROJECTILE_MATH_H_INCLUDED

#define squared(x) x*x

#include <wx/math.h>
#include <wx/wx.h>

struct Vector{
double x;
double y;
};

class Projectile_math{

public: Projectile_math();///Empty constructor...just initialises variables
        Projectile_math(double Accele,int x_scale_f,int y_scale_f);///Create constructor

        ~Projectile_math();///Destructor

        void Initialise();
        double DegreesToRad(double Degrees);
        double RadToDegrees(double Radians);
        double KpHToMpS(double KilometersPerHour);
        double X_distance(double time,double angle_Rad,double Initial_Velocity);
        double Y_distance(double time,double angle_Rad,double Initial_Velocity);
        wxInt16 X_scaled_distance(double X_distance_in_meters,int max_horizontal);
        wxInt16 Y_scaled_distance(double Y_distance_in_meters,int max_vertical);

        bool SetScaleFactor(int x_scale_f,int y_scale_f);///Set scale factor
        double GetCurrentVelocity(void);
        double GetCurrentTime(void);
        double GetCurrentYDistance(void);
        void SetCurrentYDistance(double distance);
        double GetCurrentXDistance(void);
        double GetCurrentAcceleration(void);
        double GetCurrentAngle(void);

private:const double pi=3.14159265358979;
        double Acceleration;///  m/s^2
        int X_scale_factor;
        int Y_scale_factor;
        double Time;
        double Init_Velocity;
        double angle;

        double Current_Y_distance;
        double Current_X_distance;
        double Current_Acceleration;///If variable acceleration is used(requires the use of CALCULUS MATHEMATICS)

};

#endif // PROJECTILE_MATH_H_INCLUDED
