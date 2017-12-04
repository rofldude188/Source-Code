#include <iostream>
#include <stdlib.h>
using namespace std;
int GCD(int a, int b) {
	if (b == 0) {
		return a;
	}
	return GCD(b, a % b);
}
void swap(int data[], int i, int j) {

  int tmp = data[i];

  data[i] = data[j];

  data[j] = tmp;

}
int main(const int argc, const char* const argv[]) {
	if (argc < 3) {
		cerr << "Error: Unable to compute GCD and/or LCM because invalid number of inputs." << endl;
	}
	else if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
		cerr << "Error: Unable to compute GCD and/or LCM because arguments must be greater than 0." << endl;
	}
	else if (argc > 3) {
		cerr << "Warning: Expected 2 arguments but received " << argc - 1 << "; ignoring extraneous arguments." << endl;
	}
	else {
		//int x = atoi(argv[1]);
		//int y = atoi(argv[2]);
		//int gcd = GCD(x, y);
		//int lcm = x / gcd * y / gcd * gcd;;
		//cout << "GCD(" << x << "," << y << ")" << " = " << gcd << endl;
		//cout << "LCM(" << x << "," << y << ")" << " = " << lcm << endl;
		//int a = 45;
	//int b = 0;
   //cout << (a && b) << endl;
   int a = 5;
   int b = a;
	a++;
	cout << a << endl;
	cout << b << endl;

}
return 0;
	}
	


