//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//


//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

int range(const int dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
bool sort(int dataset[], const int size);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  Return -1 if there there are any problems with the dataset.
//
void msort(int dataset[], int lowIndex, int midIndex, int highIndex){
	int L [midIndex - lowIndex + 2];
	for (int i = lowIndex; i <= midIndex; i++) {
    L[i - lowIndex] = dataset[i];
}
L[midIndex - lowIndex + 1] = 2147483646;
int R [highIndex - midIndex + 1];

for (int i = midIndex + 1; i <= highIndex; i++) {
    R[i - midIndex - 1] = dataset[i];
}
R[highIndex - midIndex] = 2147483646;
int i = 0, j = 0;

for (int k = lowIndex; k <= highIndex; k++) {
    if (L[i] <= R[j]) {
        dataset[k] = L[i];
        i++;
    }
    else {
        dataset[k] = R[j];
        j++;
    }
} 
}
void merge(int arr[], int l, int r)
{
    if (l == r){
		return;
	}
	else
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = (l+r)/2;
 
        // Sort first and second halves
        merge(arr, l, m);
        merge(arr, m+1, r);
 
        msort(arr, l, m, r);
    }
}
int range(const int dataset[], const int size){
	if(size <= 1){
		return -1;
	}
	int min = 2147483646;
	int max = 0;
	for(int i = 0; i < size; i++){
		if(dataset[i] < min)
			min = dataset[i];
		if(dataset[i] > max)
			max = dataset[i];
	}
	return max - min;
	}

int mode(const int dataset[], const int size, int mode[]){
	int checker = -500;
	int counter = 1;
	int counter2 = 0;
	int maxfrequency = -2147483646;
	if(size <= 1){
		return -1;
	}
	else{
		int arr [size];
		for(int i = 0; i < size; i++){
			arr[i] = dataset[i];
		}
		if(sort(arr, size)){
				
			
			
	for(int i = 0; i < size - 1; i++){
		for(int j = i + 1; j < size; j++){
		if(arr[i] == arr[j]){
			
			counter++;
		}
		
		
	}
	if(counter > maxfrequency){
		maxfrequency = counter;
	}
	
	counter = 1;
		}
		if(maxfrequency == 1){
			return 0;
		}
		counter = 0;
		for(int i = 0; i < size - 1; i++){
			for(int j = i+1; j < size; j++){
				if(arr[i] == arr[j]){
					counter2++;
				}
			}
			if(counter2 + 1 == maxfrequency){
				mode[counter] = arr[i];
				counter++;
			}
			counter2 = 0;
		}
	}
	return counter;
				
				
		
}
}
bool sort(int dataset[], const int size){
	if(size == 0){
		return false;
	}
	
	else{
		merge(dataset, 0, size-1);
		return true;
	}

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
  
  // Some test driver code here ....
  int data[10000];
  for(int i = 0; i < 9998; i++){
	  data[i] = i;
  }
  data[9998]= 1;
  data[9999] = 1;
  int size = 10000;
  //change this to however many modes you expect to find
  int modeArray[100]={0};
  //msort(data, 0, size - 1);
  int rng = range(data, size);
  int modes = mode(data, size, modeArray);

  for(int i = 0; i < size; i++){
	  cout << data[i] << endl;
  }
  cout << "range: " << rng << " number of Modes: " << modes << " Modes are this: ";
  for(int i = 0; i<modes;i++){
  	cout<< modeArray[i];
  	if(i<modes-1){
  		cout << ", ";
  	}
  }
  cout<<endl;
  return 0;
}

#endif
