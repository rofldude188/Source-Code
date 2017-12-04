//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

float NthRoot(const float S, const int N, const float precision);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the Nth root of S with
// precision.
//
float pow(float a, float b) {
	if (b == 0) {
		return 1;
	}
	int counter = 0;
	float result = 1;
	while (counter < b) {
		result = result * a;
		counter++;
	}
	return result;
}
float abs(float a) {
	if (a < 0) {
		return -1 * a;
	}
	return a;
}
float NthRoot(const float S, const int N, const float precision) {
	float z = S / N;
	if(S < 0 && N % 2 == 0){
		return std::numeric_limits<float>::quiet_NaN();
	}
	if(N < 2){ 
		return std::numeric_limits<float>::quiet_NaN();
	}
	if(precision <= 0){
		return std::numeric_limits<float>::quiet_NaN();
	}
	while (abs(((S - pow(z, N)) / S)) >= precision) {
		z = (((N - 1.0) / N)*z) + (S / (N*pow(z, N- 1.0)));
	}
	return z;

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
  
  if (argc < 4) {
    cerr << "Error: Usage: " << argv[0] << " <number> <root> <precision>; exiting" << endl;
    return -1;
  }

  float root = NthRoot(atof(argv[1]),atoi(argv[2]),atof(argv[3]));
  if (isNaN(root))
    cerr << "Unable to compute " << argv[2] << "th root of " << argv[1] << " with precision " << argv[3] << endl;
  else
    cout << "Root(" << argv[1] << "," << argv[2] << ") = " << root << endl
	 << "(with precision " << argv[3] << ")" << endl; 

  return 0;
}

#endif
