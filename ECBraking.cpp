#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;
int main(const int argc, const char* const argv[]) {
	if (argc < 4) {
		cerr << "Error: Insufficient arguments; expecting 3 arguments." << endl;
	}
	else {
		if (argc > 4) {
			cerr << "Warning: Expecting three command-line arguments; received " << argc - 1 << "; ignoring extraneous arguments." << endl;
		}
		float velocity = atof(argv[1]);
		float distance = atof(argv[2]);
		float maximumdeceleration = atof(argv[3]);
		float deceleration;
		float stoppingtime;
		float finalvelocity;
		if (atof(argv[3]) < 0) {
			cout << "Deceleration rate cannot be negative." << endl;
		}
		else if (velocity == 0) {
			cout << "There is no possibility of collision because the velocity of the car is 0." << endl;
		}
		else if (distance == 0) {
			cout << "There is no possibility of collision because the distance to the obstacle is 0." << endl;
		}
		else if (velocity > 0 && distance < 0) {
			cout << "There is no possibility of collision because velocity vector is heading opposite direction from obstacle." << endl;
		}
		else if (velocity < 0 && distance > 0) {
			cout << "There is no possibility of collision because velocity vector is heading opposite direction from obstacle." << endl;
		}
		else {
			deceleration = fabs(pow(velocity, 2) / (2 * distance));
			stoppingtime = fabs(velocity / deceleration);
			if (fabs(deceleration) < fabs(maximumdeceleration)) {
				cout << "Initial car velocity: " << velocity << "m/s" << endl;
				cout << "Distance to obstacle: " << distance << "m" << endl;
				cout << "Minimum deceleration: " << deceleration << "m/s/s" << endl;
				cout << "Maximum stopping time: " << stoppingtime << "s" << endl;
			}
			else {
				if (distance < 0) {
					finalvelocity = sqrt(pow(velocity, 2) + 2 * maximumdeceleration*distance);
					stoppingtime = fabs((finalvelocity + velocity) / (maximumdeceleration));
				}
				else {
					finalvelocity = sqrt(pow(velocity, 2) - 2 * maximumdeceleration*distance);
					stoppingtime = fabs((finalvelocity - velocity) / (maximumdeceleration));
				}

				cout << "Crash will occur in " << stoppingtime << " seconds at velocity " << finalvelocity << "m/s" << "; deploying airbags.";
				}
			}
		}
	}
	
	
