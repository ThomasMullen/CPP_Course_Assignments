# CPP_Course_Assignments
8 Assignments that were used to assess my progress in my undergraduate OOP module
// Assignment 1 - calculate transition energy using simple Bohr formula

//Program Function:
/*
The Bohr model allows the photon energies of electron transitions to be calculated.
Ask the user to enter the atomic number, initial and final quantum numbers, and then asks the user whether to print out the energy of the transition in J or eV. Contains Checks for valid inputs
*/

//Include headers
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<limits>

using namespace std;

//Define Global variables
const double electron{ 1.602e-19 };
bool y {true};

//Define Functions

//Electron volt function

double photon_energy_eV(int atomic_number, int initial_quantumNumber, int final_quantumNumber){
	double energy_diff;
	energy_diff = -13.6*pow(atomic_number,2)*((1 / pow(initial_quantumNumber,2)) - (1 / pow(final_quantumNumber,2)));
	return energy_diff;
}

//Joules function

double photon_energy_J(int atomic_number, int initial_quantumNumber, int final_quantumNumber){
	double energy_diff;
	energy_diff = -13.6*electron*pow(atomic_number, 2)*((1 / pow(initial_quantumNumber, 2)) - (1 / pow(final_quantumNumber, 2)));
	return energy_diff;
}

int main(){

	while (y){

		//declare variables
		int n_initial, n_final;
		double Energy_J;
		double Energy_eV;
		int atomic_number;

		// Ask user to enter atomic number

		cout << "Please enter the atomic number you, Z:" << endl;	
		cin >> atomic_number; cout << endl;

		//check atomic number is valid  
		
		while (cin.fail() || atomic_number > 118 || atomic_number <= 0 || cin.peek() != '\n'){
			cout << "Sorry the atomic number was not vaild!" << endl << " Remember it must be an integer within 1 and 118." << endl;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin >> atomic_number;
		}

		// Ask user to enter initial and final quantum numbers

		cout << "Please enter your initial quantum value followed by your final quantum value:" << endl;		
		cin >> n_initial; //input initial QM state
		cin >> n_final; //input final QM state

		//test if QM # positive integer

		while (cin.fail() || n_initial <= 0 || n_final <= 0 || cin.peek() != '\n'){
			cout << "Quantum nubers need to be positive integer and non-zero" << endl << "please eneter the initial quantum state followed by the final state:" << endl;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> n_initial;
			cin >> n_final;
		}

		//test if initial QM # > final QM #

		while (n_initial < n_final || n_initial == n_final){
			cout << "Initial Quantum state must be greater than final state to emitt photon" << endl << "please eneter the initial quantum state followed by the final state" << endl;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> n_initial;
			cin >> n_final;
		}

		// ask if he want answer in eV or Joules

		while (true){
			cout << "Do you want your answer in Joules or eV?" << endl;
			string conversion;
			vector <string> poss_J{ "Joules", "joules", "J", "j", "Joule", "joule" }; //accepted Joule inputs
			vector <string> poss_eV{ "e", "eV", "EV", "ev", "electron Volts" }; //accepted eV inputs
			cin >> conversion;

			//User has selected Joules and spit out answer	
			if (std::find(poss_J.begin(), poss_J.end(), conversion) != poss_J.end()){
				Energy_J = photon_energy_J(atomic_number, n_initial, n_final);
				cout << "The photon energy of the energy transition is: " << setprecision(4) << Energy_J << " J" << endl;
				break;
			}

			//User has selected eV and display answer
			if (std::find(poss_eV.begin(), poss_eV.end(), conversion) != poss_eV.end()){
				Energy_eV = photon_energy_eV(atomic_number, n_initial, n_final);
				cout << "The photon energy of the energy transition is: " << setprecision(4) << Energy_eV << " eV" << endl;
				break;
			}

			//No valid unit selection
			else{
				cout << "You have not selected Joules or eV." << endl;
			}				
		}
		
		//repeat operation
		
		cout << "Repeat? [y/n]" << endl;
		char choice;
		cin >> choice;
		if (choice == 'n'){
			y = false;
		}
		
	}

	return 0;
}
