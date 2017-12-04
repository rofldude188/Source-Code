//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
#include <cmath>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) {
	if(v == 0){
		destX = 0;
		destY = h;
		return true;
	}
	if(m == 0){
		return false;
	}
	if(theta == 90){
		destX = 0;
		destY = h;
		return true;
	}
	float g = 9.8;
	
	destX = (pow(v,2)/(2*g))*(1+sqrt(1+(2*g*h)/(pow(v,2)*pow(sin(theta*(M_PI/180)), 2))))*sin(2*theta*(M_PI/180));
	float time = destX/(v*cos(theta*(M_PI/180)));
	//destY = 0;
	float checker = v*sin(theta*(M_PI/180))*time - 1/2*g*(pow(time,2));
	if(checker < t){
		destY = destX - checker;
		destX = b;
	}
	//cout << time << endl;
	
	return true;
	
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....

  float h = 50;
  float v = 18.4;
  float m = 1;
  float theta = 17.89;        // Angle in degrees; will need to be converted by function
  float d = 100;
  float t = 60;
  float b = 30;
  float w = 20;

  float hitsAtX;
  float hitsAtY;

  if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
    cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
  else
    cout << "Unable to calculate where projectile hits." << endl;
  return 0;
}

#endif
