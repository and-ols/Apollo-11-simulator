/***************************************************
 * Header File:
 *    STAR
 * Author:
 *    Andrew Olson, Michael Darling
 * Summary:
 *    Keeps track of everything to do with the star 
 *    including the phase and position of the star.
***************************************************/

#include <iostream>
#include "point.h"
#pragma once
using namespace std;

/********************************************
* STAR
* This class keeps track of everything
* to do with the stars.
*******************************************/
class Star
{
private:
   unsigned char phase;
   Point pt;

public:
   // Constructor.
   Star(const Point& ptUpperRight);

   // Getters.
   Point getPoint() { return this->pt; }
   unsigned char getPhase() { return phase; }

   // Setters.
   void progressPhase() { phase++; }
};