//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <stdlib.h>
#include <cmath>
#include <cfloat>
#include <math.h>
#include <limits>
#include <fstream>
//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//
using namespace std;
#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// struct definitions 
//
#ifndef MARMOSET_TESTING
struct Student{
	int studentID;
	int grade;
};

struct Dataset{
	int numStudents;
	Student* students;
};

struct Rejects{
	int numRejects;
	int* rejects;
};

struct Mode{
	int numModes;
	int* modes;
};

struct Statistics{
	int   minimum;
	float average;
	int   maximum;
	float popStdDev;
	float smplStdDev;
	Mode  mode;
	int   histogram[10];
};
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//
int readCSV(const char filename[],const int minAcceptableID, 
				const int maxAcceptableID,Dataset& data, 
				Rejects& rejects);

int computeStatistics(Dataset& data, Statistics& stats);

int writeCSV(const char filename[], const Statistics& stats);

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//
int readCSV(const char filename[],const int minAcceptableID, 
				const int maxAcceptableID,Dataset& data, 
				Rejects& rejects){
		char filename1 [100];
		int a = 0;
		int endcounter;
		bool z = true;
		while(filename[a] != '\0'){
			if(filename[a] == '.'){
				z = false;
			}
			if(filename[a+1] == '\0'){
				endcounter = a + 1;
			}
			filename1[a] = filename[a];
			a++;
		}
		if(z){
			filename1[endcounter] = '.';
			filename1[endcounter+1] = 'c';
			filename1[endcounter+2] = 's';
			filename1[endcounter+3] = 'v';
			filename1[endcounter+4] = '\0';
		}
		if(minAcceptableID > maxAcceptableID){
			return -1;
		}
		int maxNumErrors = 10;
		int maxNumStudents = 100;
		rejects.numRejects = 0;
		rejects.rejects = new int [maxNumErrors];
		data.students = new Student [maxNumStudents];
		const int maxLineLength = 100;
		char line[maxLineLength];
		std::ifstream infile;            // declare the file object
		if(!z)
		infile.open(filename);      // open the file
		else
		infile.open(filename1);	
		if (!infile.is_open())
			return -1;                // Unable to open file
		 
		bool done = false;
		bool x = false;
		bool p = false;
		bool h = false;
		bool n = false;
		bool m = false;
		int fileLineNumber = 0;
		int i = 0;
		int num = 0;
		int num2 = 0;
		int counter2 = 0;
		int counter = 0;
		int numofvalidstudentcounter = 0;
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
						if(line[i] == ' '){
							int j = i;
							int k = i;
							while(line[j] != '\0'){
								if(line[j] == ' '){
									j++;
								}
								else if(line[j] < '0' || line[j] > '9'){
								break;
								}
								else{
									n = true;
									break;
								}
								
							}
							while(k != 0){
								//if(line[k] >= '0' && line[k] <= '9'){
								if(line[k] == ' '){
									k--;
								}
								else if(line[k] < '0' || line[k] > '9'){
								break;
								}
								else{
									m = true;
									break;
								}
							}
						}
						if(m && n){
							h = true;
						}
						if(line[i] != ' ' && line[i] != ',' && line[i] != '\t' && line[i] != '\n' && (line[i] < '0' || line[i] > '9')){
							h = true;
						}
							if(line[i] == ',' && p){
							h = true;
						}
						if(line[i] == ',' && !p){
							p = true;
							x = true;
						}
						if(line[i+1] == '\0' && !x){
							h = true;
						}
						if(!x && line[i] >= '0' && line[i] <= '9'){
							num = num * 10 + line[i] - '0';
							
						}
						if(x && line[i] >= '0' && line[i] <= '9'){
							num2 = num2 * 10 + line[i] - '0';
						}
					i++;	
				}

				if(h || num < minAcceptableID || num > maxAcceptableID || num2 < 0 || num2 > 100){
					rejects.numRejects++;
					rejects.rejects[counter] = fileLineNumber;
					counter++;
					if(counter == 10){
						return -1;
					} 
				}
				else{
					
				data.students[counter2].studentID = num;
				data.students[counter2].grade = num2;

				numofvalidstudentcounter++;
				counter2++;
				}
				
				num = 0;
				num2 = 0;
			i = 0;
			m = false;
			n = false;
			x = false;
			h = false;
			p = false;
			}
		}
		data.numStudents = numofvalidstudentcounter;

	return rejects.numRejects;
}
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
float avg(int arr[], int size){
	float num = 0;
	float size1 = (float) size;
	for(int i = 0; i < size; i++){
		num += (float) arr[i];
	}
	return num/size1;
}
float PopStandardDeviation(int dataset[], int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float summation = 0;
	for(int i = 0; i < size; i++)
		summation += pow(((float)dataset[i] - avg(dataset, size)), 2);
	return sqrt(summation / ((float)(size)));
}
float SampStandardDeviation(int dataset[], int size) {
	if(size < 2)
		return std::numeric_limits<float>::quiet_NaN(); 
	float summation = 0;
	for(int i = 0; i < size; i++)
		summation += pow(((float)dataset[i] - avg(dataset, size)), 2);
	return sqrt(summation / ((float)(size - 1)));
}
int mode(int dataset[], int size, int mode []){
	bool p = false;
	for(int i = 0; i < size; i++){
		if(dataset[i] == dataset[i+1]){
			p = true;
		}
	}
	if(!p){
		for(int i = 0; i < size; i++){
			mode[i] = dataset[i];
		}
		return size;
	}
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
	return counter;
				
				
		
}
}
int computeStatistics(Dataset& data, Statistics& stats){
	int arrayofgrades [data.numStudents];
	int arrayofmodes [data.numStudents];
	stats.mode.modes = new int [data.numStudents];
	for(int i = 0; i < 10; i++){
		stats.histogram[i] = 0;
	}
	for(int i = 0; i < data.numStudents; i++){
		arrayofgrades[i] = data.students[i].grade;
	}
	bubbleSort(arrayofgrades, data.numStudents);
	for(int i = 0; i < data.numStudents; i++){
	}
	stats.minimum = arrayofgrades[0];
	stats.maximum = arrayofgrades[data.numStudents - 1];
	stats.average = avg(arrayofgrades, data.numStudents);
	stats.popStdDev = PopStandardDeviation(arrayofgrades, data.numStudents);
	stats.smplStdDev = SampStandardDeviation(arrayofgrades, data.numStudents);
	stats.mode.numModes = mode(arrayofgrades, data.numStudents, arrayofmodes);
	for(int i = 0; i < stats.mode.numModes; i++){
		stats.mode.modes[i] = arrayofmodes[i];
	}
	for(int i = 0; i < data.numStudents; i++){
		stats.histogram[arrayofgrades[i]/10]++;
	}
	return 0;
}

int writeCSV(const char filename[], const Statistics& stats){
	int i = 0;
	int dotindex;
	int dotcounter = 0;
	int endindex;
	char newfilename [100];
	while(filename[i] != '\0'){
		if(filename[i] == '.'){
			dotcounter++;
			dotindex = i;
		}
		if(filename[i+1] == '\0'){
			endindex = i+1;
		}
		newfilename[i] = filename[i];
		i++;
	}
	if(dotcounter > 1){
		return -1;
	}
	if(dotcounter == 1){
		newfilename[dotindex+1] = 's';
		newfilename[dotindex+2] = 't';
		newfilename[dotindex+3] = 'a';
		newfilename[dotindex+4] = 't';
		newfilename[dotindex+5] = '\0';
	}
	if(dotcounter == 0){
		newfilename[endindex] = '.';
		newfilename[endindex+1] = 's';
		newfilename[endindex+2] = 't';
		newfilename[endindex+3] = 'a';
		newfilename[endindex+4] = 't';
		newfilename[endindex+5] = '\0';
	}
	ofstream outfile;
	outfile.open(newfilename);
	if(!outfile.is_open())
		return -1;
	
	outfile << "Minimum: " << stats.minimum << endl;
	outfile << "Average: " << stats.average << endl;
	outfile << "Maximum: " << stats.maximum << endl;
	outfile << "Population Standard Deviation: " << stats.popStdDev << endl;
	outfile << "Sample Standard Deviation: " << stats.smplStdDev << endl;
	outfile << "Modes: ";
	for(int i = 0; i < stats.mode.numModes; i++){
		if(i != stats.mode.numModes - 1)
		outfile << stats.mode.modes[i] << ", ";
		else
		outfile << stats.mode.modes[i] << endl;
	}
	outfile << "Histogram:" << endl;
	outfile << "[0-9]: " << stats.histogram[0] << endl;
	outfile << "[10-19]: " << stats.histogram[1] << endl;
	outfile << "[20-29]: " << stats.histogram[2] << endl;
	outfile << "[30-39]: " << stats.histogram[3] << endl;
	outfile << "[40-49]: " << stats.histogram[4] << endl;
	outfile << "[50-59]: " << stats.histogram[5] << endl;
	outfile << "[60-69]: " << stats.histogram[6] << endl;
	outfile << "[70-79]: " << stats.histogram[7] << endl;
	outfile << "[80-89]: " << stats.histogram[8] << endl;
	outfile << "[90-100]: " << stats.histogram[9] << endl;
	outfile.close();
	return 0;
}
//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  	
	// Some test driver code here ....
	int minAcceptableID = 0;
	int maxAcceptableID = 22299999;

	Dataset data = {0};
	Rejects rejects = {0};
	Statistics stats = {0};

	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;

	if(readCSV(argv[1], minAcceptableID, maxAcceptableID, data, rejects) < 0)
	{
		std::cout << ".csv file could not be read" << std::endl;
	}

	if (computeStatistics(data, stats) < 0)
	{
		std::cout << "Stats could not be computed" << std::endl;
	}

	if (writeCSV(argv[1], stats) < 0)
	{
		std::cout << ".stat file could not be written" << std::endl;
	}

	std::cout << "Average: " << stats.average << std::endl;
	std::cout << "Minimum: " << stats.minimum << std::endl;
	std::cout << "Maximum: " << stats.maximum << std::endl;
	std::cout << "Population standard deviation: " << stats.popStdDev << std::endl;
	std::cout << "Sample standard deviation: " << stats.smplStdDev << std::endl;
	
	
	for (unsigned char i = 0; i < stats.mode.numModes; i++)
	{
		std::cout << "Mode: " << stats.mode.modes[i] << std::endl;
	}

	for (unsigned char i = 0; i < 10; i++)
	{
		std::cout << "Histogram bin [" << (i*10) << ", " << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
	}
	for (int i = 0; i < rejects.numRejects; ++i){
		cout << "rejects " << rejects.rejects[i] << endl;
	}

	return 0;
}

#endif
