//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
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
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
              const float d, const float step, const float k,
              const float t, const float b, const float w, float& v);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
float f (const float vFake, const float h, const float t, const float theta, const float d, const float step, const float k, const float m){ //drag function
	float trueTheta = (theta* (M_PI/180));
	float cosTheta = cos(trueTheta);
	float sinTheta = sin(trueTheta);
	float currentVx = vFake * cosTheta; 
	float currentVy = vFake * sinTheta;
	float currentVtotal = vFake;
	float currentPosY = h;
	float currentPosX = 0;
	float currentDragX = 0;
	float currentDragY = 0;
	float currentAccelerationX = 0;
	float currentAccelerationY = -9.8;
	bool p = true;
	int counter = 0;
	if(h < t){
		
while(p || currentPosY >= t){
	if(counter == 20000){
		//cout << "current posx " << currentPosX << endl;
		break;
	}
			if(currentPosY >= t){
				p = false;
			}
			currentDragX = currentVx * currentVtotal * k;
		currentAccelerationX = -currentDragX/m;
		currentVx = currentVx + (currentAccelerationX * step);
		//y
		currentDragY = currentVy * currentVtotal * k;
		currentAccelerationY = (-9.8*m - currentDragY)/m;
		currentVy = currentVy + (currentAccelerationY * step);
		//
		currentVtotal = sqrt((currentVx * currentVx) + (currentVy * currentVy));
		currentPosY = currentPosY + (currentVy * step);
		currentPosX = currentPosX + (currentVx * step);
		counter++;
		}
		return currentPosX;
	}
else{
	
	
	//cout << " T " << t << endl;
	while(currentPosY >= t){
		//if(currentPosX >= d){
		//	cout << currentPosY << endl;
		//}
		//x
		currentDragX = currentVx * currentVtotal * k;
		currentAccelerationX = -currentDragX/m;
		currentVx = currentVx + (currentAccelerationX * step);
		//y
		currentDragY = currentVy * currentVtotal * k;
		currentAccelerationY = (-9.8*m - currentDragY)/m;
		currentVy = currentVy + (currentAccelerationY * step);
		//
		currentVtotal = sqrt((currentVx * currentVx) + (currentVy * currentVy));
		currentPosY = currentPosY + (currentVy * step);
		currentPosX = currentPosX + (currentVx * step);
			//	cout << "Current X position " << currentPosX << endl;
		//cout << "Current Y velocity " << currentVy << endl;
	}
	return currentPosX;	
}
}


float bisectionHelper(const float left, const float right,
		      const float precision, const float theta, const float t, const float h, const float step, const float k, const float d, const float m, const float minIntervalSize, int numberofIterations){
	//if(numberofIterations==100 || isnan(f(left, h, t, theta, d, step, k, m)) || isnan(f(right, h, t, theta, d, step, k, m))){
	//	return std::numeric_limits<float>::quiet_NaN();
	//}

	float midpoint = (left + right)/2.0;
	float interval = right - left;
			  if(fabs(d - fabs(f(midpoint, h, t, theta, d, step, k, m))) < precision || fabs(interval) < minIntervalSize){
				//  cout << "a" << endl;
		return midpoint;
	}
	if(interval < minIntervalSize && fabs(d - fabs(f(midpoint, h, t, theta, d, step, k, m))) > precision){
		//cout << "b" << endl;
		return midpoint;
	}
	if(f(left, h, t, theta, d, step, k, m) < d){
	if(f(midpoint, h, t, theta, d, step, k, m) < d){
		//cout << "c" << endl;
		return bisectionHelper(midpoint, right, precision, theta, t, h, step, k, d, m, minIntervalSize, numberofIterations + 1);
	}
	else{
		//cout << "d" << endl;
		return bisectionHelper(left, midpoint, precision, theta, t, h, step, k, d, m, minIntervalSize, numberofIterations + 1);
	}
	}
	else{
		if(f(midpoint, h, t, theta, d, step, k, m) > d){
			//cout << "e" << endl;
			//cout << "THIS IS WHAT VELOCITY IS PASSED TO FUNCTION " << midpoint << endl;
			//cout << "THIS IS WHAT POSX IS GETTING FROM FUNCTION " << f(midpoint, h, t, theta, d, step, k, m) << endl;
		return bisectionHelper(left, midpoint, precision, theta, t, h, step, k, d, m, minIntervalSize, numberofIterations + 1);
	}
	else{
		//cout << "f" << endl;
		return bisectionHelper(midpoint, right, precision, theta, t, h, step, k, d, m, minIntervalSize, numberofIterations + 1);
	}
	}
			  }

float bisection(const float left, const float right,
		const float precision, const float theta, const float t, const float h, const float step, const float k, const float d, const float m, const float minIntervalSize) {
		//if(f(left, h, t, theta, d, step, k, m)/f(right, h, t, theta, d, step, k, m) > 0 || precision <= 0 || minIntervalSize <= 0 || left >= right){
		//return std::numeric_limits<float>::quiet_NaN();
	//}
	if(fabs(d - fabs(f(left, h, t, theta, d, step, k, m))) <= precision){
		//cout << "a" << endl;
		return left;
	}
	 if(fabs(d - fabs(f(right, h, t, theta, d, step, k, m))) <= precision){
		 //cout << "b" << endl;
		return right;
	}
		//cout << "c" << endl;
		return bisectionHelper(left, right, precision, theta, t, h, step, k, d, m, minIntervalSize, 0);

}
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float step, const float k,
              const float t, const float b, const float w, float& v) {
	if(k == 0){
		float x = d;
	float g = 9.8;
	float y = t - h;
	float a = x*sin(2*theta*(M_PI/180));
	float c = 2*y*pow(cos(theta*(M_PI/180)),2);
	float e = pow(x, 2)*g;
	
	float vmin = sqrt(e/(a-c));
	v = vmin;
		return true;
	}
	else{
		float x = d;
	float g = 9.8;
	float y = t - h;
	float a = x*sin(2*theta*(M_PI/180));
	float c = 2*y*pow(cos(theta*(M_PI/180)),2);
	float e = pow(x, 2)*g;
	
	float vmin = sqrt(e/(a-c));
	//cout << "vmin " << vmin << endl;
	float vmax = 100;
		v = bisection(vmin, vmax, 0.001, theta, t, h, step, k, d, m, 0.001);
		return true;
	}
	
	

}		

#ifndef MARMOSET_TESTING
int main() {
	float tester = 33.0505;
	
  // Some test driver code here ....
  float h = 30;
  float d = 60;
  float b = 40;
  float t = 70;
  float w = 30;
  float m = 0.5;
  float step = 0.003;
  float k = 0.003;
  float theta = 67.96; // Angle in degrees;
  float v = 25;	
	float tester2 = f(tester, h, t, theta, d, step, k, m);
	cout << "This should be equal to d which is 60 " << tester2 << endl;

  cout << endl << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, step, k, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity" << endl << endl;
  }
    
  return 0;
}
#endif