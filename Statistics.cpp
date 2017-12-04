#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdlib.h>
#include <cfloat>
using namespace std;
int main(const int argc, const char* const argv[]) {
	int counter = 0;
	if (argc == 1) {
		cerr << "Unable to compute statistics over data because there are no arguments" << endl;
	}
	else if (argc == 2) {
		cerr << "Unable to compute stastics over data because there is only 1 argument" << endl;
	}
	else {
		float max = 0;
		float min = FLT_MAX;
		float sum = 0;
		cout << "Number of floating-point numbers: " << argc - 1 << endl;
		while (counter < argc - 1) {
			float x = atof(argv[counter + 1]);
			if (x > max) {
				max = x;
			}
			if (x < min) {
				min = x;
			}
			sum += x;
			counter++;
		}
		cout << "Minimum floating-point number: " << min << endl;
		cout << "Average floating-point number: " << sum / (argc - 1) << endl;
		cout << "Maximum floating-point number: " << max << endl;
	}
}