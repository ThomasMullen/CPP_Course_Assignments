// ConsoleApplication1.cpp : Defines the entry point for the console application.
/*Notes:

*/

#include "stdafx.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>
using namespace std;

//template <typename T>
//void write_vector(const vector<T>& V){
//    for (int i = 0; i < V.size(); i++)
//        cout << V[i] << " " << endl;
//}

//This function returns the integer code of th ecourse address
int returnCode(string courseName){
	//collect string separated by space
	size_t pos = courseName.find(' ');
	string courseCode = courseName.substr(0, pos);
	try{
		int code = stoi(courseCode);
		return code;
	}
	catch (...){
		cerr << "You did not enter a valid course address." << endl;
		return -1;
	}
}

//This function returns the string course title of th course address
string returnTitle(string courseName){
	//collect string separated by space
	size_t pos = courseName.find(' ');
	string courseTitle = courseName.substr(pos + 1);
	return courseTitle;
}

//Sorts the function in alphabetical order
bool titleSort(string s1, string s2){
	s1.erase(0, 10);
	s2.erase(0, 10);
	return s1<s2;
}

//Get moduels of a specific year
vector<string> getModuleOfYear(char Year, vector<string>& CourseModuleVec ){
	vector <string> course_Year_Vec;

	for (int i{ 0 }; i < CourseModuleVec.size(); i++){
		if (CourseModuleVec[i].at(5) == Year){
			course_Year_Vec.push_back(CourseModuleVec[i]);
		}
		//else{
			//cout << CourseModuleVec[i] << ", isn't " << Year <<" year module." << endl;
		//}
	}
	return course_Year_Vec;
}


int main()
{
	const string degreeCode("PHYS");
	string courseAddress;
	vector <string> CourseNameVec;
	vector <string> CourseAddVec;
	vector <int> CourseCodeVec;
	bool not_finished(true);

	
	// storing data as a vector of strings
	//Description
	cout << "\n\nThis code will be allow you to store and range of course adresses and print out the list in either alphabetical or numerical order. It will also allow you to input your what year you are in a print out all the modules available for your year.\n\n" << endl;
	
	// Gather list of courses and their codes from user,
	do{


		//Enter Course Name
		cout << "Please enter a course name (or x to finish): " << endl;
		getline(cin, courseAddress);

		//escape command
		if (courseAddress == "x"){ break; }

		//Separate course address into integer code and string title
		int code = returnCode(courseAddress);
		if (code < 0){
			return 1;
		}
		string courseName = returnTitle(courseAddress);


		//string stream & extract as string & append to single vector (course address vector)
		ostringstream ofss;
		ofss << degreeCode << ' ' << code << ' ' << courseName;
		string outputDegreeAddress{ ofss.str() };
		CourseAddVec.push_back(outputDegreeAddress);
		ofss.str(""); //clear string stream



	} while (not_finished);

	//ask the user what what list sorting is required
	while (true){
		cout << "Do you want your course list sorted in numerical (N) or alhpabetical order (A)?" << endl;
		string sortPrefence;
		//possible options
		vector <string> poss_Alpha{ "A", "a", "Alphabetical", "Alphabetical" }; //accepted alphabetical inputs
		vector <string> poss_Numb{ "N", "n", "Numerical", "Numerical" }; //accepted numerical inputs
		cin >> sortPrefence;

		//User has selected numerical order
		if (find(poss_Numb.begin(), poss_Numb.end(), sortPrefence) != poss_Numb.end()){
			// sort for numerical
			vector <string> ::iterator intBegin{ CourseAddVec.begin() }, intEnd{ CourseAddVec.end() };
			sort(intBegin, intEnd);
			break;
		}

		//User has selected alphabetical order and display answer
		if (find(poss_Alpha.begin(), poss_Alpha.end(), sortPrefence) != poss_Alpha.end()){
			//sort for alphabetical use a function on the final bracket
			vector <string> ::iterator titleBegin{ CourseAddVec.begin() }, titleEnd{ CourseAddVec.end() };
			sort(titleBegin, titleEnd, titleSort);
			break;
		}

		//No valid unit selection
		else{
			cerr << "Please select alphabetical (A) or numerical (N)." << endl;
		}
	}

	//Print sorted vector
	for (auto courseCodeIter = CourseAddVec.begin(); courseCodeIter < CourseAddVec.end(); courseCodeIter++)
		cout << *courseCodeIter << endl;

	//Find what year the user is in and print out available modules for that year
		
	cout << "What year are you in? [1]/[2]/[3]/[4]" << endl;
	char courseYear{ '0' };
	cin >> courseYear;
	//Test valid year
	
	while (courseYear < '1' || courseYear > '4'){
		cerr << "Please enter a valid year (1, 2, 3, 4)" << endl;
		//courseYear.clear(); courseYear.ignore(numeric_limits<streamsize>::max(),'\n');
		cin >> courseYear;
	}

	vector <string> courseYearVec;

	switch (courseYear){
	case '1':
		//if year 1 selected
		cout << "You are in 1st year." << endl;
		courseYearVec = getModuleOfYear(courseYear, CourseAddVec);
		//print vector in yr 1
		
		break;

	case '2':
		//if year 2 selected
		cout << "You are in 2 year." << endl;
		courseYearVec = getModuleOfYear(courseYear, CourseAddVec);
		break;

	case '3':
		//if year 3 selected
		cout << "You are in 3rd year." << endl;
		courseYearVec = getModuleOfYear(courseYear, CourseAddVec);
		break;

	case '4':
		//if year 3 selected
		cout << "You are in 4th year." << endl;
		courseYearVec = getModuleOfYear(courseYear, CourseAddVec);
		break;

	}

	for (auto courseCodeIter = courseYearVec.begin(); courseCodeIter < courseYearVec.end(); courseCodeIter++){
		cout << *courseCodeIter << endl;
	}


	return 0;
}
/*
10471   Random Processes in Physics (M)
10191   Introduction to Astrophysics and Cosmology
10302   Vibrations and Waves
20252   Fundamentals of Solid State Physics
20312   Wave Optics
30180   Third Year Laboratory
30201   Mathematical Fundamentals of Quantum Mechanics (M)
30392   Cosmology
40222   Particle Physics
40322   Nuclear Physics
40352   Solid State Physics
40411   Soft Matter Physics
40421   Nuclear Structure and Exotic Nuclei
40422   Applied Nuclear Physics
*/