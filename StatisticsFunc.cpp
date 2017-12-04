//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <cmath>
#include <cfloat>
#include <math.h>
#include <limits>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
	        float& popSD, float& smplSD, float& mdn);

float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool statistics(const float dataset[], const int size,
	   float& min, float& avg, float& max,
	   float& popSD, float& smplSD, float& mdn) {
  min = minimum(dataset, size);
  avg = average(dataset, size);
  max = maximum(dataset, size);
  popSD = popStdDev(dataset, size);
  smplSD = smplStdDev(dataset, size);
  mdn = median(dataset, size);
	   if(isnan(min) || isnan(avg) || isnan(max) || isnan(popSD) || isnan(smplSD) || isnan(mdn))
			return false;
	   else
			return true;
}

float minimum(const float dataset[], const int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float min = FLT_MAX;
	for(int i = 0; i < size; i++)
		if(dataset[i] < min)
			min = dataset[i];
	return min;
}

float average(const float dataset[], const int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float sum = 0;
	for(int i = 0; i < size; i++)
		sum+=dataset[i];
	return sum/size;
}

float maximum(const float dataset[], const int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float max = 0;
	for(int i = 0; i < size; i++)
		if(dataset[i] > max)
			max = dataset[i];
	return max;
}

float popStdDev(const float dataset[], const int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float summation = 0;
	for(int i = 0; i < size; i++)
		summation += pow((dataset[i] - average(dataset, size)), 2);
	return sqrt(summation / (size));
}

float smplStdDev(const float dataset[], const int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float summation = 0;
	for(int i = 0; i < size; i++)
		summation += pow((dataset[i] - average(dataset, size)), 2);
	return sqrt(summation / (size - 1));
}

float median(const float dataset[], const int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float a[size];
	for(int i = 0; i < size; i++)
		a[i] = dataset[i];
	for(int n = size; n > 1; n--) 
	for(int i = 1; i < n; i++) {
	    if(a[i-1] > a[i]) {
		float tmp = a[i-1];
		a[i-1] = a[i];
		a[i] = tmp;
	    }
	}
	if(size % 2 != 0)
		return a[size/2];
	else
		return (a[size/2 - 1] + a[size/2])/2;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
  int size = argc-1;
  float dataset[size];
  for (int i = 1; i < argc; i++){
	  dataset[i-1] = atof(argv[i]);
  }
  
  float min;
  float max;
  float avg;
  float popStDev;
  float smplStDev;
  float median;

  if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, median)) {
    cout << "Minimum: " << min << endl
	 << "Average: " << avg << endl
	 << "Median:  " << median << endl
	 << "Maximum: " << max << endl
	 << "Population Standard Deviation: " << popStDev << endl
	 << "Sample Standard Deviation:     " << smplStDev << endl;
  }
  else
    cout << "Error: unable to compute statistics" << endl;

  return 0;
}

#endif
