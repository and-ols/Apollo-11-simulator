/*************************************************************
 * 1. Name:
 *      Michael Darling and Andrew Olson
 * 2. Assignment Name:
 *      Lab 06: Apollo 11 Code Complete
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      Figuring out how to use pointers and call by reference.
 *      Everything was a breeze after that.
 * 5. How long did it take for you to complete the assignment?
 *      6 hours.
 *****************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "lander.h"
#include "star.h"
#include "Velocity.h"
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Game
{
private:
   Lander lander;           // The lander
   vector<Star> stars;      // The stars
   Ground ground;           // The ground
   double gravity = 1.625;  // Meters/second.

public:
   Game(const Point& ptUpperRight) :
      ground(ptUpperRight)
   {
      for (int i = 0; i < 50; i++)
      {
         Star newStar(ptUpperRight);
         stars.push_back(newStar);
      }
   }

   // Reference getters.
   vector<Star>& starReference() { return stars; }
   Ground& groundReference() { return ground; }
   double getGravity() const { return gravity; }   
};

/********************************************************
* PARSE INPUT
* Decifer input to update velocity and lander position.
********************************************************/
void parseInput(const Interface* pUI, Game* pGame, Lander* rLander, Velocity& v)
{
   ogstream gout;

   // Sets a base value for the landers new trajectory
   double xChange = v.getDX();
   double yChange = v.getDY();
   double time = v.getTime();

   // As long as the ship is functional, check for input.
   if ((rLander->getFuel() > 0) && (rLander->stillFlying() == true))
   {
      // Adjust the trajectory based on input.
      // If input is left or right, adjust angle and fuel.
      if (pUI->isRight())
      {
         rLander->updateAngle(-0.1);
         rLander->updateFuel(1);
      }
      if (pUI->isLeft())
      {
         rLander->updateAngle(0.1);
         rLander->updateFuel(1);
      }

      // If input is down, use thrust to adjust velocity.
      if ((pUI->isDown()) && (rLander->getFuel() >= 10))
      {
         float accelerationThrust = v.computeAccelerationThrust(
            rLander->getThrust(), rLander->getWeight()) * time / 2;
         xChange += v.computeHorizontalComponent(rLander->getAngle()
            , -accelerationThrust);
         yChange += v.computeVerticalComponent(rLander->getAngle()
            , accelerationThrust);
         rLander->updateFuel(10);
      }

      // Draw the flames for the lander.
      if (rLander->getFuel() >= 10)
      {
         gout.drawLanderFlames(rLander->getPoint(), rLander->getAngle(), /*angle*/
            pUI->isDown(), pUI->isLeft(), pUI->isRight());
      }
   }
   
   // As long as the space craft is still flying,
   // whether it has fuel or not, keep moving.
   if (rLander->stillFlying() == true)
   {
      // Apply gravity.
      yChange -= pGame->getGravity() * time / 2;

      // Move the lander using the new trajectory.
      rLander->addX(xChange * time);
      rLander->addY(yChange * time);

      // Store velocity for next time.
      v.setDX(xChange);
      v.setDY(yChange);
   }
}

/************************************************************************
* CHECK LANDER STATUS
* Checks to see if the lander is in the platform, when it lands, the 
* lander is set to its upright position and stops moving. If it has 
* crashed the lander will stop moving where it has crashed, then 
* displays an end screen.
************************************************************************/
void checkLanderStatus(Ground& rGround, Lander* pLander, Velocity& v)
{
   ogstream gout;

   // Check for landing pad.
   if (rGround.onPlatform(pLander->getPoint(), pLander->getWidth()) == true)
   {
      if ((v.getSpeed() <= 4.0) && (pLander->getCrashed() == false))
      {
         v.setDX(0.0);
         v.setDY(0.0);
         pLander->updateAngle(0.0);
         pLander->hasLanded();
      }
      else
      {
         pLander->hasCrashed();
         gout.setPosition(Point(130.0, 200.0));
      }
   }

   // Check for ground.
   if (rGround.hitGround(pLander->getPoint(), pLander->getWidth()) == true)
   {
      v.setDX(0.0);
      v.setDY(0.0);
      pLander->updateAngle(0.0);
      pLander->hasCrashed();
   }

   // If the ship isn't flying, display end screen. 
   if (pLander->stillFlying() == false)
   {
      // If the ship crashed, display fail message.
      if (pLander->getLanded() == true)
      {
         gout.setPosition(Point(130.0, 200.0));
         gout << "The Eagle has landed!";
      }

      // Otherwise, display victory message. 
      else
      {
         gout.setPosition(Point(130.0, 200.0));
         gout << "Hudston, we have a problem.";
      }

      // Stop movement.
      v.setDX(0.0);
      v.setDY(0.0);
   }
}

/*****************************************************
* DRAW FLIGHT DISPLAY
* Display fuel, altitude, speed in top left corner.
*****************************************************/
void drawFlightDisplay(Lander* pLander, Velocity& v)
{
   ogstream gout;

   // Calculate speed for display and crash-checking.
   double speed = v.getSpeed();

   // Put some text on the screen.
   gout.setPosition(Point(10.0, 380.0));
   gout << "Fuel:     " << pLander->getFuel() << " lbs" << endl;
   gout << "Altitude: " << (int)pLander->getY() << endl;
   gout << "Speed:   " << fixed << setprecision(2) << speed << " m/s" << endl;

}

/********************************************************
* DRAW STARS
* Interate through each star, drawing and phasing them.
********************************************************/
void drawStars(vector<Star>& stars)
{
   ogstream gout;

   // For each star that is phasing, phase it, then remove it when it is done.
   for (auto& star : stars)
   {
      gout.drawStar(star.getPoint(), star.getPhase());
      star.progressPhase();
   }
}

/*****************************************
* DRAW SCREEN
* All of the draw functions happen here.
*****************************************/
void drawScreen(Lander* pLander, vector<Star>& rStars
   , Ground& rGround, Velocity& rV)
{
   ogstream gout;

   drawStars(rStars);
   rGround.draw(gout);
   gout.drawLander(pLander->getPoint(), pLander->getAngle() );
   drawFlightDisplay(pLander, rV);
}

/******************************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 *****************************************************/
void callBack(const Interface* pUI, void* p)
{
   ogstream gout;

   // Create pointers and references to each variable for tracking usage.
   Game* pGame = (Game*)p;
   Lander* pLander = (Lander*)p;
   vector<Star>& rStars = pGame->starReference();
   Velocity& rV = pLander->getVelocity(); // Get velocity from lander.
   Ground& rGround = pGame->groundReference();

   // Get input and modify velocity and lander accordingly.
   parseInput(pUI, pGame, pLander, rV);

   // Draw assets.
   drawScreen(pLander, rStars, rGround, rV);

   // Finally, check if lander has touched ground or landing pad.
   checkLanderStatus(rGround, pLander, rV);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Point ptUpperRight(400.0, 400.0);
   Interface ui(0, NULL,
      "Open GL Demo",
      ptUpperRight);

   // Initialize the game class
   Game game(ptUpperRight);

   // set everything into action
   ui.run(callBack, &game);

   return 0;
}
