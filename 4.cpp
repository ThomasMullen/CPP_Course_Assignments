#include "stdafx.h"
// PHYS 30762 Programming in C++
// Assignment 4

//Prgram Description:
//This program will create a class for galaxies and can store them into a vector and print them out
//member functions of the class able to rename galaxy, print out galaxy data, find stellar mass, and store satellites in galaxies

// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

class Galaxy
{
private:
	string hubbleType;
	double redshift, totalMass, stellarMassFraction;
	vector <Galaxy> satellite;

public:
	// Constructors

	//Default constructor
	Galaxy() : hubbleType("Type"), redshift(0), totalMass(0), stellarMassFraction(0) /*Vector satellite*/{}

	//Parametised constructor
	Galaxy(string PhubbleType, double Predshift, double PtotalMass, double PstellarMassFraction) :
		hubbleType(PhubbleType), redshift(Predshift), totalMass(PtotalMass), stellarMassFraction(PstellarMassFraction) {}

	// Destructor
	~Galaxy(){ cout << "Destroying " << hubbleType << endl; }

	// Return stellar mass (M_* = f_* x M_tot)
	double stellarMass() { return totalMass * stellarMassFraction; }

	// Change galaxy's Hubble type
	void changeType(string newType);

	// Prototype for function to print out an object's data
	void printData();

	// Add satellite galaxy
	void addSatellites(string hubbleType, double redshift, double totalMass, double stellarMassFraction){
		satellite.push_back(Galaxy(hubbleType, redshift, totalMass, stellarMassFraction));
	}
	void addSatellites(Galaxy g1){
		satellite.push_back(g1);
	}


};

// Print out an object's data
void Galaxy::printData(){
	cout.precision(3);//set precision 3sf
	cout << "Galaxy data:\n\n Hubble Type: " << hubbleType << "\n Redshift: " << redshift << "\n Total Mass: " << totalMass << "\n Stellar Mass Fraction: " << stellarMassFraction << "\n\n"<<endl;
	//See if galaxy contains satellites if so print the satellites
	if (satellite.size() != 0){
		vector<Galaxy>::iterator SatIt;
		for (auto SatIt = satellite.begin(); SatIt < satellite.end(); ++SatIt){
			cout << "Satellite Data: \n\n\n";
			SatIt->stellarMass();
			SatIt->printData();	
		}
	}
	return;
}

void Galaxy::changeType(string newType) {
	hubbleType = newType;
	}

// End of class and associated member functions

// Main program
int main()
{
	//Declare and define initial Galaxies
	vector<Galaxy> Galaxy_data;
	vector<Galaxy> satellite_data;
	const string Type1{ "E[0-7]" }, Type2{ "S0" }, Type3{ "S[A-C]" }, Type4{ "SB[a-c]" }, Type5{ "Irr" };

	// Example using parameterised constructor
	Galaxy G1{ Type1, 3, 1.43e8, 0.02 };
	Galaxy G2{ Type2, 8, 7.54e9, 0.4 };
	Galaxy G3{ Type3, 2, 3.54e8, 0.52 };
	Galaxy G4{ Type4, 3, 1.84e9, 0.7 };
	Galaxy G5{ Type5, 5, 1.6e10, 0.12 };

	// Example using default constructor
	Galaxy g1;

	// Add satellite galaxies and set to default constructor
	G2.addSatellites(g1);//add default galaxy to G2
	G2.addSatellites(G3);


	//Pushback galaxies into vector
	Galaxy_data.push_back(g1);
//	Galaxy_data.push_back(G1);
	Galaxy_data.push_back(G2);
//	Galaxy_data.push_back(G3);
//	Galaxy_data.push_back(G4);
	Galaxy_data.push_back(G5);

	// print out data
	vector<Galaxy>::iterator pcur;
	for (auto pcur = Galaxy_data.begin(); pcur < Galaxy_data.end(); ++pcur){
		pcur->printData();
		
		// Get and print out stellar mass
		cout << "Stellar mass: " << pcur->stellarMass() << endl;
	}

	// Rename Hubble type from Irr to S0
	G2.changeType(Type5);
	vector<Galaxy> Galaxy_RenameData;
//	Galaxy_RenameData.push_back(G1);
	Galaxy_RenameData.push_back(G2);
//	Galaxy_RenameData.push_back(G3);
//	Galaxy_RenameData.push_back(G4);
	Galaxy_RenameData.push_back(G5);

	//Print Editted Galaxies
	for (auto pcur = Galaxy_RenameData.begin(); pcur < Galaxy_RenameData.end(); ++pcur){
		pcur->printData();
		// Get and print out stellar mass
		cout << "Stellar mass: " << pcur->stellarMass() << endl;
	}
		
	return 0;
}
