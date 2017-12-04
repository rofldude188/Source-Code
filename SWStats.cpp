#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdlib.h>
#include <cfloat>
using namespace std;
int main(const int argc, const char* const argv[]) {
	if (argc < 3) {
		cerr << "Error: Insufficient number of arguments." << endl;
	}
	else if (atoi(argv[1]) <= 0) {
		cerr << "Error: Unable to compute statistics over data set because window size cannot be less than or equal to 0." << endl;
	}
	else if (atoi(argv[1]) == 1) {
		cerr << "Warning: The window size is one." << endl;
	}
	else if (atoi(argv[1]) > (argc - 2)) {
		cerr << "Warning: Window size is greater than input" << endl;
	}
	else {
		int counter = 0;
		int windowsize = atoi(argv[1]);
		float max = 0;
		float min = FLT_MAX;
		float sum = 0;
		float a[(argc - 1) + windowsize - 2];
		for (int i = 0; i < (windowsize - 1); i++) {
			a[i] = atof(argv[2]);
		}
		cout << "Window Size: " << windowsize << endl;
		cout << "Sample " << "Value " << "SWMinimum " << "SWAverage " << "SWMaximum" << endl;
		while (counter < argc - 2) {
			a[counter + (windowsize - 1)] = atof(argv[counter + 2]);
			counter++;
		}
		counter = 1;
		for (int i = windowsize; i < argc + windowsize - 2; i++) {
			for (int j = counter - 1; j < i; j++) {
				if (a[j] > max) {
					max = a[j];
				}
				if (a[j] < min) {
					min = a[j];
				}
				sum += a[j];
			}
			cout << counter << " " << argv[counter + 1] << " " << min << " " << sum / windowsize << " " << max << " " << endl;
			min = FLT_MAX;
			max = 0;
			sum = 0;
			counter++;
		}
	}
}