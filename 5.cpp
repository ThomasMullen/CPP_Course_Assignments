#include "stdafx.h"
// PHYS 30762 Programming in C++
// Assignment 5: Class for complex numbers

//Project description:

//This program will create a class that can store complex numbers
//constant memebr functions that can return: re, im, modulus, arg. of the the complex number
//operational overload memebr funcitons: multiply, divide, add and subtract values of class complex
//call friend functions to i/o stream variables assigned to complex class as it acts left of the variable
// complex variable inputted by user are a and b

//Headers and constants
#include<iostream>
#include<cmath>
#include<string>

#define PI 3.14159265
using namespace std;

// Class for complex numbers:
// In this complex class private data will have real and imaginary doubles
// there will be public member functions to return values described in the desciption
//and will include friend overloads for cin and cout.
class complex
{


private:
	double re, im;
public:
	// Constructors & destructor
	complex(){ re = im = 0; }
	complex(double r, double i){ re = r; im = i; }
	~complex(){}

	// Return real component
	double getReal()const{ return re; }
	// Return imaginary component
	double getIm()const{ return im; }
	// Return modulus
	double getMod()const{ return sqrt(pow(re, 2) + pow(im, 2)); }
	// Return argument
	double getArg()const {
		if (im < 0){ return 360 + atan2(im, re) * 180 / PI; }
		else{ return atan2(im, re) * 180 / PI; }
	}
	// Return complex conjugate
	complex getComplConj()const{
		complex z_conj(re, -im);
		return z_conj;
	}

	// Overload + operator for addition
	complex operator+(const complex& z)const{
		complex sum(re + z.re, im + z.im);
		return sum;
	}
	// Overload - operator for subtraction
	complex operator-(const complex& z)const{
		complex minus(re - z.re, im - z.im);
		return minus;
	}
	// Overload * operator for multiplication, z1*z2
	complex operator*(const complex& z)const{
		double RealPart{ re*z.re - im*z.im };
		double ImPart{ im*z.re + re*z.im };
		complex product(RealPart, ImPart);
		return product;
	}
	// Overload / operator for division, z1/z2
	complex operator/(const complex& z)const{
		double denominator{ z.getMod() };
		complex temp(re, im);
		complex numerator = temp*z.getComplConj();
		complex quotient(numerator.re / denominator, numerator.im / denominator);
		return quotient;
	}

	// Make function to overload operator<< & operator>> a friend
	friend ostream & operator<<(ostream& os, const complex& z);
	friend istream & operator>>(istream& is, complex& z);
};

// Non-member function to overload ostream (e.g., cout) for complex z
ostream & operator<<(ostream &os, const complex& z)
{
	os << showpos << "(" << z.re << " " << z.im << "i)" << endl;
	return os;
}

//Input test validity
double NumberCheck(string temp){
	double test; bool valid{ false };
	while (!valid){
		try{
			test = stod(temp);
			valid = true;
		}
		catch (...){
			cerr << "Invalid input. Please enter a number." << endl;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> temp;
		}
		
	}
	return test;
}

// Non-member function to overload istream (e.g., cin) for complex z
istream & operator>>(istream& is, complex& z)
{
	string temp;
	cout << "Please enter the real part of your complex number a +/- bi: ";
	is >> temp;
	z.re = NumberCheck(temp);
	
	cout << "Please enter the imaginary part of your complex number a +/- bi: ";
	is >> temp;
	z.im = NumberCheck(temp);
	return is;
}


int main()
{
	//program description
	cout << "Description\n\nThis program has a complex number class which allows the user to input complex number and operate on these numbers.\nConstant member functions that can return: re, im, modulus, arg. of the the complex number.\nOperational overload memebr funcitons: multiply, divide, add and subtract values of class complex.\nCall friend functions to i/o stream variables assigned to complex class as it acts left of the variable.\n\n";
	cout.precision(3);

	// Create two complex numbers
	//    complex a(3, 4);
	//    complex b(1, -2);


	//Istream complex number
	complex a, b;
	cin >> a;
	cout << "The complex number, a, you inserted: " << a << endl;
	cin >> b;
	cout << "The complex number, b, you inserted: " << b << endl;

	// Get real and imaginary components, modulus and argument
	cout << "a:" << endl << "Real part : " << a.getReal() << " Im part : " << a.getIm() << endl;
	cout << "Modulus: " << a.getMod() << " Argument: " << a.getArg() << "\370\n" << endl;
	cout << "b:" << endl << "Real part: " << b.getReal() << " Im part: " << b.getIm() << endl;
	cout << "Modulus: " << b.getMod() << " Argument: " << b.getArg() << "\370\n" << endl;
	// Get conjugates
	cout << "Complex conjugate of a = " << a.getComplConj() << "Complex conjugate of b = " << b.getComplConj() << endl;

	// Get sum, difference, product and quotient of a and b
	cout << "Division (a / b): " << (a / b) << endl;
	cout << "Multiplication (a * b): " << (a * b) << endl;
	cout << "Sum (a + b): " << (a + b) << endl;
	cout << "Subtraction (a - b): " << (a - b) << endl;

	return 0;
}