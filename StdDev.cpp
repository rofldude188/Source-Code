#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <cfloat>
using namespace std;
int main(const int argc, const char* const argv[]) {
	if (argc == 1) {
		cerr << "Error: Unable to compute statistics over data because there are no arguments" << endl;
	}
	if (argc == 2) {
		cout << "Number of floating-point numbers: " << argc - 1 << endl;
		cout << "Minimum floating-point number: " << argv[1] << endl;
		cout << "Average floating-point number: " << argv[1] << endl;
		cout << "Maximum floating-point number: " << argv[1] << endl;
		cout << "Population standard deviation: " << 0 << endl;
		cout << "Sample standard deviation: " << "infinity" << endl;
	}
	else {
		int counter = 0;
		float sum = 0;
		float a[argc - 1];
		while (counter < argc - 1) {
			a[counter] = atof(argv[counter + 1]);
			sum += a[counter];
			counter++;
		}
		counter = 0;
		float average = sum / (argc - 1);
		float max = 0;
		float min = FLT_MAX;
		float summation = 0;
		while (counter < argc - 1) {
			summation += pow((a[counter] - average), 2);
			if (a[counter] > max) {
				max = a[counter];
			}
			if (a[counter] < min) {
				min = a[counter];
			}
			counter++;
		}
		float popsd = sqrt(summation / (argc - 1));
		float samsd = sqrt(summation / (argc - 2));
		cout << "Number of floating-point numbers: " << argc - 1 << endl;
		cout << "Minimum floating-point number: " << min << endl;
		cout << "Average floating-point number: " << average << endl;
		cout << "Maximum floating-point number: " << max << endl;
		cout << "Population standard deviation: " << popsd << endl;
		cout << "Sample standard deviation: " << samsd << endl;
	}
}