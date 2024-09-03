/*************************************
 * Header File:
 *    LANDER
 * Author:
 *    Andrew Olson, Michael Darling
 * Summary:
 *    This files tracks everything to
 *    do with the lander class.
 ************************************/

#pragma once
#include "point.h"
#include "Velocity.h"

// Implement
enum Status {FLYING, CRASHED, LANDED};

/********************************************
* LANDER
* This class keeps track of everything 
* to do with the lander.
*******************************************/
class Lander
{
private:
   bool flying = true;
   bool crashed = false;
   bool landed = false;
   Point ptLM = Point(400, 350);
   Velocity v;
   double angle = 0.0;      // Angle of lander in radians.
   double fuel = 5000.0;    // Fuel left in lander.
   double weight = 15103.0; // Weight of the lander.
   double thrust = 45000;   // Thrust of the lander.
   int width = 20;          // Lander width.

public:
   // Getters.
   bool stillFlying() const { return flying; }
   bool getCrashed() const { return crashed; }
   bool getLanded() const { return landed; }
   double getWeight() const { return weight; }
   double getThrust() const { return thrust; }
   double getAngle() const { return angle; }
   double getFuel() { return fuel; }
   int getWidth() const { return width; }
   double getX() const { return ptLM.getX(); }
   double getY() const { return ptLM.getY(); }
   Velocity& getVelocity() { return v; }
   Point getPoint() { return ptLM; }

   // Setters.
   void hasLanded();
   void hasCrashed();
   void updateAngle(float radians) { angle += radians; }
   void updateFuel(int change) { this->fuel -= change; }
   void addX(double xChange) { ptLM.addX(xChange); }
   void addY(double yChange) { ptLM.addY(yChange); }
};