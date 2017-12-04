//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <fstream>
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

int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return -1 if you cannot compute the histogram for any
// reason;
// Return 0 if the histogram is correct and there are no
// rejections;
// Return the number of rejects if there are rejected
// records from the file
//

int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects) {
		if(minAcceptableID > maxAcceptableID){
			return -1;
		}
		if (histogram == NULL){
			return -1;
		}
		int maxNumErrors = 100;
		for(int i = 0; i < 10; i++){
		histogram[i] = 0;
		}
		rejects = new int [maxNumErrors];
		const int maxLineLength = 100;
		char line[maxLineLength];
		std::ifstream infile;            // declare the file object
		infile.open(filename);      // open the file
		if (!infile.is_open())
			return -1;                // Unable to open file
		 
		bool done = false;
		bool x = false;
		bool p = false;
		int fileLineNumber = 0;
		int i = 0;
		int num = 0;
		int num2 = 0;
		int counter = 0;
		int linecounter = 1;
		int numofrejects = 0;
		while (!done) {  
			++fileLineNumber;
			if (!infile.getline(line, maxLineLength)) { // Get next line
				if (infile.eof()) {                       // End of file
					done = true;
				}
				else{
					return -1;
				}
			}
			if(!done){
				while(line[i] != '\0'){
						if(line[i] != ' ' && line[i] != ',' && line[i] != '\t' && line[i] != '\n' && (line[i] < '0' || line[i] > '9')){
							return -1;
						}
						if(line[i] == '-'){
							p = true;
						}
							
						if(line[i] == ','){
							x = true;
						}
						if(!x && line[i] >= '0' && line[i] <= '9'){
							num = num * 10 + line[i] - '0';
							
						}
						if(x && line[i] >= '0' && line[i] <= '9'){
							num2 = num2 * 10 + line[i] - '0';
						}
					i++;	
				}
				if(p == true || num < minAcceptableID || num > maxAcceptableID || num2 < 0 || num2 > 100){
					numofrejects++;
					rejects[counter] = linecounter;
					counter++;
				}
				else{
					histogram[num2/10]++;
				}
				num = 0;
				num2 = 0;
			i = 0;
			x = false;
			linecounter++;
			}
		}
			return numofrejects;
		}
		
				  
  // Your code here ...


//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  if (argc < 2) {

  }
  const int numBuckets = 10;
  const int bucketRange = 100/numBuckets;
  int buckets[numBuckets];
  int* rejectedRecords;
  int retCode = histogram(argv[1], buckets, 22200000, 22299999, rejectedRecords);
  if (retCode < 0) {
      cout << "Unable to compute histogram." << endl;
  }
  else {
    for (int i = 0; i < numBuckets; ++i)
      if (i != numBuckets-1)
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
      else
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
    if (retCode > 0) {
      cout << "Number of rejected records: " << retCode << endl;
      cout << "Rejected records are:";
      for (int i = 0; i < retCode; ++i)
	cout << " " << rejectedRecords[i];
      cout << endl;
      delete[] rejectedRecords;
    }
  }

  return 0;
}

#endif
