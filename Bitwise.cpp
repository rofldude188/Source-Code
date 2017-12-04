#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
int main(const int argc, const char* const argv[]) {
	int N = atoi(argv[1]);
	int S = atoi(argv[2]);
	cout << "N: " << N << endl;
	cout << "S: " << S << endl;
	cout << "Left-shift of N by S bits is: " << (N << S) << endl;
	cout << "Right-shift of N by S bits is: " << (N >> S) << endl;
	cout << "The equivalent math operation of left-shift N by S bits is: N*2^S" << endl;
	cout << "And the result of the operation is: " << N*pow(2, S) << endl;
	cout << "The equivalent math operation of right-shift N by S bits is: N/2^S" << endl;
	cout << "And the result of that operation is: " << N / pow(2, S) << endl;
}