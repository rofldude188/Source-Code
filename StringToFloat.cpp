//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
// You are allowed float.h
#include <math.h>	
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

bool stringToFloat(const char input[], float& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...

bool stringToFloat(const char input[], float& value) {
	bool p = true;
	bool z = false;
	float sign = 1;
	float sign2 = 1;
	int index = 0;
	int counter = 0;
	int counter2 = 0;
	float power = 1;
	if(input[0]=='e' || input[0] == 'E'){
		return false;
	}
	if(input[0]=='+'){
		sign = 1;
	}
	else if(input[0] == '-'){
		sign = -1;
	}
	float num = 0;
	float num2 = 0;
	for(int i = index; input[i]!= 0; i++){
		if(input[i] == '+' || input[i] == '-'){
			if(input[i+1] == '-' || input[i+1] == '+'){
				return false;
			}
		}
		if(input[i] == ' '){
			return false;
		}
		if(input[i] != '+' && input[i] != '-' && input[i] != 'E' && input[i] != 'e' && input[i] != '.' && (input[i] < 48 || input[i] > 57)){
			return false;
		}
		if(input[i] == '.'){
			p = false;
			counter++;
			if(input[i+1] < 48 || input[i+1] > 57){
				return false;
			}
			//float z = (input[i+1] - 48)/10.0;
			//value = num + z;
			//return true;
		}
		if(z){
			if(input[i] == '+'){
				sign2 = 1;
			}
			if(input[i] == '-'){
				sign2 = -1;
			}
			if(input[i] > 48 && input[i] <= 57){
				num2 = num2 * 10 + input[i] - 48;
				//num = num * pow(10.0, sign2*num2);
				//value = num * sign;
				//return true;
			}
		}
		if(input[i] == 'e' || input[i] == 'E'){
			counter2++;
			if(input[i+1] != '+' && input[i+1] != '-' && (input[i+1] < 48 || input[i+1] > 57)){
				return false;
			}
			z = true;
			/*if(input[i+1] < 48 || input[i+1] > 57){
				return false;
			}
			for(int j = i; input[j]!=0; j++){
				
			if(input[j+1] == '+'){
				sign2 = 1;
				num = num * pow(10.0, input[j+2] - 48);
				value = num;
				return true;
			}
			if(input[j+1] == '-'){
				sign2 = -1;
				num = num * pow(10.0, sign2*(input[j+2] - 48));
				value = num * sign;
				return true;
			}
			if(input[j+1] > 48 && input [j+1] <= 57){
				num = num * pow(10.0, input[j+1] - 48);
				value = num * sign;
				return true;
			}
			}*/
		}
		if(!z && p && input[i] >= 48 && input[i] <= 57){
		num = num * 10 + input[i] - 48;
		}
		if(!z && !p && input[i] >= 48 && input[i] <= 57){
			power = power * 10.0;
			//for(int i = 0; i < counter; i++){
			//	power = power * 10;
			//}
			num = num + (input[i] - 48)/power;
		}
	}
	if(z){
	num = num * pow(10.0, sign2*num2);
	}
	if(counter > 1 || counter2 > 1){
		return false;
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
int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  float argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
    return -1;
  }

  if (stringToFloat(argv[1],argv1)) 
    cout << "argv[1] is a float with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
  return 0;
}

#endif
