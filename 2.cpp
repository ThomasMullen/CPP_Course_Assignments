// Read in Data File and Find Average and Standard Error
/* Notes:

*/

//Headers
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<limits>

using namespace std;

// Functions to compute mean and standard deviation

// MeanFunction
double FindMean(int N, double* x){
	//declare variable
	double mean{ 0 };
	double sum{ 0 };

	//define array
	for (int i = 0; i < N; i++){
		sum += x[i]; //add and assign array element to sum
		mean = sum / N;
	}
	return mean;
}

//Standard Dev Function
double FindSD(int N, double mean, double* x){
	//declare variables
	mean = FindMean(N, x);
	double sum{ 0 };
	double SD{ 0 };

	//SD operation
	for (int i = 0; i < N; i++){
		sum += pow(x[i] - mean, 2);
		SD = sqrt(sum / (N - 1));
	}
	return SD;
}

//Standard error function
double FindStdErr(int N, double SD, double* x){
	double StdErr{ 0 };
	StdErr = FindSD(N, FindMean(N, x), x) / sqrt(N);
	return StdErr;
}

//Main Function

int main() {
	//Declare Variables
	string dataPoint;

	//Decribe function
	cout << "This program will be used to read in a data file and calculate the Mean and Standard deviation" << endl;

	//Open file
	cout << "Please enter the data file name you would like to read in: " << endl;
	// filepath{ "" };
	string fileName;
	getline(cin, fileName);
	fstream dataFile(fileName);

	//Check if Success
	if (dataFile.fail()){
		cerr << "Error: file can not be opened." << endl;
		return(1);
	}

	//Read In File Once: count the number of valid lines

	//while not end of file:
	int lineValue{ 0 };

	while (!dataFile.eof()){
		//increment line count
		lineValue++;

		//skip line
		dataFile.ignore(numeric_limits<streamsize>::max(), '\n');		
	}

	cout << "Number of overall lines read: " << lineValue << "." << endl;

	//Calculate size of valid data points
	//int NumberOfDataPoints = lineValue - badLine;

	//Close file
	dataFile.clear();
	dataFile.close();

	//Allocate Memory
	double *myData = new double[lineValue];
	cout << "Allocate memory for " << lineValue << " double(s)" << endl;

	//Read file into an array
	fstream data(fileName);

	for (int i{ 0 }; i < lineValue; i++){
		data >> myData[i];
		//		cout << myData[i] << endl;

		// Test if data point rouge
		while (data.fail() ){
			lineValue--; //Reduce array
			data.clear(); data.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Rogue data point on line: " << i + 1 << ". Data point has not been included" << endl;
			data >> myData[i]; //Push next data point in the failed element
			break;
		}
	}
	cout << lineValue << endl;

	data.close();

	//Print array out
	for (int i{ 0 }; i < lineValue; i++){
		cout << myData[i] << endl;
	}

	//Calculations
	double mean = FindMean(lineValue, myData);
	double SD = FindSD(lineValue, mean, myData);
	double SE = FindStdErr(lineValue, SD, myData);
	cout.setf(ios::fixed, ios::floatfield); // set values to same dp
	cout << "The mean value of the data is: (" << setprecision(5) << mean << " +/- " << SE << ")." << endl << " The Standard Deviation is: " << SD << "." << endl;

	//Free Memory
	delete[] myData;
	cout << "Freed Memory" << endl;

	return 0;
}