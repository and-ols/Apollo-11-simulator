/*********************************************************
 * Source File:
 *    VELOCITY.h
 * Author:
 *    Andrew Olson, Michael Darling
 * Summary:
 *    Keeps track of everything to do with the velocity
 *    including changes in x and y.
 ********************************************************/

#include "Velocity.h"

/**********************************************************************
* ADJUST VELOCITY
* This applies the acceleration to velocity, and set acorring values.
**********************************************************************/
double Velocity::adjustVelocity(double acceleration, double angle)
{
   // Get change in velocity.
   double velocity = getSpeed() + acceleration;
   dx = computeVerticalComponent(-velocity, angle);
   dy = computeHorizontalComponent(velocity, angle);
   return dx, dy;
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double Velocity::computeHorizontalComponent(double angle, double speed)
{
   return sin(angle) * speed;
}

/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double Velocity::computeVerticalComponent(double angle, double speed)
{
   return cos(angle) * speed;
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double Velocity::computeTotalComponent(double horComp, double vertComp)
{
   return sqrt((horComp * horComp) + (vertComp * vertComp));
}

/**************************************************
 * COMPUTE ACCELERATION THRUST
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double Velocity::computeAccelerationThrust(double force, double mass)
{
   return force / mass;
}
