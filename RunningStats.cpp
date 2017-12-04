#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdlib.h>
#include <cfloat>
using namespace std;
//take into account negative???
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
		cout << "Sample " << "Value " << "Minimum " << "Average " << "Maximum" << endl;
		while (counter < argc - 1) {
			float x = atof(argv[counter + 1]);
			if (x > max) {
				max = x;
			}
			if (x < min) {
				min = x;
			}
			sum += x;
			cout << counter + 1 << " " << x << " " << min << " " << sum / (counter + 1) << " " << max << " " << endl;
			counter++;
		}
	}
}