/*******************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Andrew Olson, Michael Darling
 * Summary:
 *    Keeps track of everything to do with the velocity
 *    including changes in x and y.
*******************************************************/

#pragma once

#include <iostream>

/********************************************
* VELOCITY
* This class keeps track of everything
* to do with velocity.
*******************************************/
class Velocity
{
private:
   double dx = -6.0;
   double dy = 0;
   double time = 0.1;

public:
   // Getters
   double getDX() const { return dx; }
   double getDY() const { return dy; }
   double getSpeed() { return computeTotalComponent(getDX(), getDY()); }
   double getTime() { return time; }

   // Setters
   void setDX(double dx) { this->dx = dx; }
   void setDY(double dy) { this->dy = dy; }

   // Computations
   double computeHorizontalComponent(double angle, double speed);
   double computeVerticalComponent(double angle, double speed);
   double computeTotalComponent(double horComp, double vertComp);
   double computeAccelerationThrust(double force, double mass);
   double adjustVelocity(double acceleration, double angle);
};