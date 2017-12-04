//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN() 
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta);
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta) {
	float thetaz = 45;
	float g = 9.8;
	float destX = (pow(v,2)/(2*g))*(1+sqrt(1+(2*g*h)/(pow(v,2)*pow(sin(thetaz*(M_PI/180)), 2))))*sin(2*thetaz*(M_PI/180));
	if(d > destX){
		return false;
	}
	float x = d;
	
	float y = t - h;
	float root = (v*v*v*v) - (g*(g*(x*x) + 2*y*(v*v)));
	if(root < 0){
		return false;
	}
	root = sqrt(root);
	float angle1 = atan(((v*v)+root)/(g*x))*(180/M_PI);
	float angle2 = atan(((v*v)-root)/(g*x))*(180/M_PI);
	theta = angle1;
	//theta = angle2;
	return true;
	// Your code here...
}

bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v) {
	float x = d;
	float g = 9.8;
	float y = t - h;
	float a = x*sin(2*theta*(M_PI/180));
	float c = 2*y*pow(cos(theta*(M_PI/180)),2);
	float e = pow(x, 2)*g;
	
	float initialvelocity = sqrt(e/(a-c));
	v = initialvelocity;
	return true;
	// Your code here...

}
		

#ifndef MARMOSET_TESTING
int main() {
	
  // Some test driver code here ....
  
  float h = 50;
  float d = 60;
  float b = 40;
  float t = 0;
  float w = 30;
  float m = 1;

  float theta = 68.81; // Angle in degrees;
  float v = 45.21;	

  cout << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity\n\n";
  }

  cout << "Given initial velocity: " << v << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenVelocity (h, v, m, d, t, b, w, theta)) {
    cout << "required angle: " << theta << endl << endl;
  }
  else {
    cout << "cannot calculate the angle\n\n";  
  }
    
  return 0;
}
#endif
