/*************************************
 * Source File:
 *    STAR.h
 * Author:
 *    Andrew Olson, Michael Darling
 * Summary:
 *    This files tracks everything to
 *    do with the star class.
 ************************************/

#include "Star.h"

/************************************************************************
* CONSTRUCTOR
* Create a new star with a random phase and point.
************************************************************************/
Star::Star(const Point& ptUpperRight)
{
   phase = rand() % 256;
   pt.setX(rand() % (int)ptUpperRight.getX());
   pt.setY(rand() % (int)ptUpperRight.getY());
}