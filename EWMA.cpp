#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdlib.h>
#include <cfloat>
using namespace std;
int main(const int argc, const char* const argv[]) {
	if (argc < 5) {
		cerr << "Error: Insufficient number of arguments." << endl;
	}
	else if (atoi(argv[2]) <= 0) {
		cerr << "Error: Age limit can't be less than or equal to 0." << endl;
	}
	else if (atof(argv[1]) <= 0 || atof(argv[1]) > 1) {
		cerr << "Error: Alpha value must be between 0 and 1." << endl;
	}
	else {
		float alpha = atof(argv[1]);
		int agelimit = atoi(argv[2]);
		int counter = 2;
		int agecounter1 = 1;
		int agecounter2 = 1;
		float max = 0;
		float min = FLT_MAX;
		float oldewma;
		float ewma = atof(argv[3]);
		cout << "Sample " << "Value " << "Minimum " << "EWMA " << "Maximum" << endl;
		while (counter < argc - 1) {
			float x = atof(argv[counter + 1]);
			oldewma = ewma;
			if (x > max || agecounter1 == agelimit) {
				max = x;
				agecounter1 = 1;
			}
			else {
				agecounter1++;
			}
			if (x < min || agecounter2 == agelimit) {
				min = x;
				agecounter2 = 1;
			}
			else {
				agecounter2++;
			}
			ewma = alpha * x + (1 - alpha) * oldewma;
			cout << counter - 1 << " " << x << " " << min << " " << ewma << " " << max << " " << endl;
			counter++;
	}
	}
}