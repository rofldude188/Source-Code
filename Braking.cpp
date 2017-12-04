#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdlib.h>
using namespace std;
int main(const int argc, const char* const argv[]) {
	float velocity = atof(argv[1]);
	float distance = atof(argv[2]);
	cout << "Initial car velocity:" << velocity << "m/s" << endl;
	cout << "Distance to obstacle" << distance << "m" << endl;
	float deceleration = -1 * pow(velocity, 2) / (2 * distance);
	float stoppingtime = -1 * velocity / deceleration; 
	cout << "Minimum deceleration:" << deceleration << "m/s/s/" << endl;
	cout << "Maximum stopping time:" << stoppingtime << "s" << endl;
}