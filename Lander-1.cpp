/*************************************
 * Source File:
 *    LANDER.h
 * Author:
 *    Andrew Olson, Michael Darling
 * Summary:
 *    This files tracks everything to
 *    do with the lander class.
 ************************************/

#include "Lander.h"

/************************************************************************
* HAS LANDED
* Update lander to no longer fly when it has landed.
************************************************************************/
void Lander::hasLanded()
{
   landed = true;
   flying = false;
   angle = 0.0;
}

/**************************************************************************
* HAS CRASHED
* Update lander to no longer fly when it has crashed.
**************************************************************************/
void Lander::hasCrashed()
{
   crashed = true;
   flying = false;
   angle = 52.0;
}