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


// Sample function for which you need to find the root

float f(const float x) {
  return -1.0*x*x*x + 4*x + 1;
}

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

float bisectionHelper(const float left, const float right,
		      const float precision, const float minIntervalSize
		      ... );
float bisection(const float left, const float right,
		const float precision, const float minIntervalSize);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

float bisectionHelper(const float left, const float right,
		      const float precision, const float minIntervalSize, int numberofIterations){
	if(numberofIterations==100 || isnan(f(left)) || isnan(f(right))){
		return std::numeric_limits<float>::quiet_NaN();
	}

	float midpoint = (left + right)/2.0;
	float interval = right - left;
			  if(fabs(f(midpoint)) < precision || fabs(interval) < minIntervalSize){
		return midpoint;
	}
	if(interval < minIntervalSize && f(midpoint) > precision){
		return midpoint;
	}
	if(f(left) < 0){
	if(f(midpoint) < 0){
		return bisectionHelper(midpoint, right, precision, minIntervalSize, numberofIterations + 1);
	}
	else{
		return bisectionHelper(left, midpoint, precision, minIntervalSize, numberofIterations + 1);
	}
	}
	else{
		if(f(midpoint) > 0){
		return bisectionHelper(midpoint, right, precision, minIntervalSize, numberofIterations + 1);
	}
	else{
		return bisectionHelper(left, midpoint, precision, minIntervalSize, numberofIterations + 1);
	}
	}
			  }

float bisection(const float left, const float right,
		const float precision, const float minIntervalSize) {
		if(f(left)/f(right) > 0 || precision <= 0 || minIntervalSize <= 0 || left >= right){
		return std::numeric_limits<float>::quiet_NaN();
	}
	if(fabs(f(left)) <= precision){
		return left;
	}
	 if(fabs(f(right)) <= precision){
		return right;
	}

		return bisectionHelper(left, right, precision, minIntervalSize, 0);

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
	int a = 2;
	int b = 3;
	cout << bisection(a, b, 0.001, 0.001) << endl;
  
  // Some test driver code here ....

  return 0;
}

#endif
