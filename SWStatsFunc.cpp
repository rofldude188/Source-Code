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

int SWStats(const float dataset[], const int size,
	    const int currentSample, const int windowSize,
	    float& min, float& avg, float& max,
	    float& smplSD, float& mdn);

int SWMinimum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& minimum);
int SWAverage(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& average);
int SWMaximum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& maximum);
int SWSmplStdDev(const float dataset[], const int size,
		 const int currentSample, const int windowSize,
		 float& smplStdDev);
int SWMedian(const float dataset[], const int size,
	     const int currentSample, const int windowSize,
	     float& median);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

int SWStats(const float dataset[], const int size,
	    const int currentSample, const int windowSize,
	    float& min, float& avg, float& max,
	    float& smplSD, float& mdn) {
			if(size < 2)
				return -1;
			else if(windowSize <= 0)
				return -1;
			else if(windowSize == 1)
				return 1;
			else if(windowSize >= size)
				return 1;
			else{
				if((SWMinimum(dataset, size, currentSample, windowSize, min)==0) && (SWAverage(dataset, size, currentSample, windowSize, avg)==0) && (SWMaximum(dataset, size, currentSample, windowSize, max)==0) && (SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD)==0) && (SWMedian(dataset, size, currentSample, windowSize, mdn)==0))
					return 0;
				else
					return -1;
			//min = SWMinimum(dataset, size, currentSample, windowSize, min);
			//avg = SWAverage(dataset, size, currentSample, windowSize, avg);
			//max = SWMaximum(dataset, size, currentSample, windowSize, max);
			//smplSD = SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD);
			//mdn = SWMedian(dataset, size, currentSample, windowSize, mdn);
			//return 0;
			}
}

int SWMinimum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& minimum) {
			  float min = FLT_MAX;
			  for(int i = currentSample - 1; i >= currentSample - windowSize; i--){
				  if(dataset[i] < min){
					  min = dataset[i];
				  }
			  }
			  minimum = min;
			  return 0;
}

int SWAverage(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& average) {
			  float sum = 0;
			  for(int i = currentSample - 1; i >= currentSample - windowSize; i--){
					  sum += dataset[i];
			  }
			  average = sum / windowSize;
			  return 0;
		    
}

int SWMaximum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& maximum) {
			float max = 0;
			  for(int i = currentSample - 1; i >= currentSample - windowSize; i--){
				  if(dataset[i] > max){
					  max = dataset[i];
				  }
			  }
			  maximum = max;
			  return 0;
}

int SWSmplStdDev(const float dataset[], const int size,
		 const int currentSample, const int windowSize,
		 float& smplStdDev) {
			 return 0;
}

int SWMedian(const float dataset[], const int size,
	     const int currentSample, const int windowSize,
	     float& median) {
			 return 0;
			 
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
  int counter = 0;
  int windowSize = atoi(argv[1]);
  int size = argc - 1;
  int currentSample = windowSize;
  float dataset[(argc + windowSize - 2)];
  float min;
  float avg;
  float max;
  float smplSD;
  float median;
  float a[(argc + windowSize - 3)];
	for (int i = 0; i < (windowSize - 1); i++) {
		a[i] = atof(argv[2]);
	}
	while (counter < argc - 2) {
		a[counter + (windowSize - 1)] = atof(argv[counter + 2]);
		counter++;
	}
	for (int i = 0; i < argc + windowSize - 3; i++){
	  dataset[i] = a[i];
  }
  
  for(int i = 0; i < argc + windowSize - 3; i++){
	  cout << "This is what dataset looks like " << dataset[i] << endl;
  }
  cout << "Sample \t Minimum \t Average \t Median \t Maximum \t Sample Standard Deviation" << endl;

  while (currentSample < argc + windowSize - 2) {
    int retCode = SWStats(dataset, size, currentSample, windowSize, min, avg, max, smplSD, median);
    if (retCode >= 0) {
      cout << currentSample - windowSize + 1 << "\t " << min << "\t " << avg << "\t " << median << "\t " << max << "\t " << smplSD << endl;
      if (retCode > 0)
	cerr << "Warning: something weird happened, but we computed stats anyway ... YMMV" << endl;
    }
    else {
      cerr << "Error: unable to compute sliding-window statistics; exiting" << endl;
      return(-1);
    }
    ++currentSample;
  }
  return 0;
}

#endif
