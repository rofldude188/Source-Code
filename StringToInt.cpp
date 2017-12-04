//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

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

bool stringToInt(const char input[], int& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool stringToInt(const char input[], int& value) {
	int sign = 1;
	int index = 0;
	if(input[0]=='+'){
		sign = 1;
		index = 1;
	}
	else if(input[0] == '-'){
		sign = -1;
		index = 1;
	}
	int num = 0;
	for(int i = index; input[i]!= 0; i++){
		if(input[i] < 48 || input[i] > 57){
			return false;
		}
		num = num * 10 + input[i] - 48;
	}
	value = num*sign;
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
  int argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <int>" << endl;
    return -1;
  }

  if (stringToInt(argv[1],argv1)) 
    cout << "argv[1] is an int with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not an int." << endl;
  return 0;
}

#endif
