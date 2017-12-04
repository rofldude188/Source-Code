#include <iostream>
#include <stdlib.h>
using namespace std;
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
int main(const int argc, const char* const argv[]) {
	if (argc < 4) {
		cerr << "Error: Unable to compute Nth root because insufficient number of arguments." << endl;
	}
	else {
		if (atoi(argv[1]) <= 0) {
			cerr << "Error: Unable to compute Nth root because base must be greater than 0." << endl;
		}
		else if (atoi(argv[2]) < 2) {
			cerr << "Error: Unable to compute Nth root because N must be greater than 1." << endl;
		}
		else if (atof(argv[3]) <= 0) {
			cerr << "Error: Unable to compute Nth root because precision can't be less than or equal to 0." << endl;
		}
		else if (argc > 4) {
			cerr << "Warning: More arguments than necessary." << endl;
		}
		else {
			float x = atof(argv[1]);
			float nthroot = atof(argv[2]);
			float precision = atof(argv[3]);
			float z = x / nthroot;
			while (abs(((x - pow(z, nthroot)) / x)) >= precision) {
				z = (((nthroot - 1) / nthroot)*z) + (x / (nthroot*pow(z, nthroot - 1)));
			}
			cout << "Root(" << x << "," << nthroot << ")" << " = " << z << endl;
			cout << "(with precision " << abs(((x - pow(z, nthroot)) / x)) << ")" << endl;
		}
	}
}