//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////                         Assignment 7 Vector Class                            //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////             Description                            ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//General cartesian vector class (x,y,z):
//default, parameterised, move and copy constructor and destructor
//accessor - returning components of the vector using () operator and check for accessing outside
//Member function: dot product. Friend function: Ostream.

//Derived class 1: Minkowski 4-vec (x,y,s,ct):
//same constructors and accessor for 4
//Member funciton: overridden dot prod, Lorentz boost. Friend: Cout<<...

//Particle Class (r,m,beta):
//parameterized constructor (taking a 4-vector, a double and a 3-vector: r∼,m,β)
//Member function: calc gamma, tot energy, mv.


//HELP::
//have to have Vector memebers as public so that the Minkowski can access them
//Help dervied accesing protected

//headers
#include "stdafx.h"
#include<iostream>
#include<limits>
#include<string>
#include<cmath>
#include<stdlib.h>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////                       Vector Class                           ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Base Class(Vector)
class Vector{
	// Friends
	friend ostream & operator<<(ostream &os, const Vector &V);

protected:
	double *component;
	int length;


public:
	//default constructor:
	Vector() :
		component(nullptr), length(0){}

	//parametised constructor
	Vector(int _length){
		length = _length; component = new double[_length];
		for (int i{ 0 }; i < length; i++){
			component[i] = 0;
		}
	}

	//Parametised constructor (components)
	Vector(double _x, double _y, double _z){
		length = 3; component = new double[length];
		component[0] = _x; component[1] = _y; component[2] = _z;
	}

	//Copy constructor
	Vector(Vector const& V)
	{
		//deep copy
	//	cout << " deep copy\n";
		component = nullptr; length = V.getLength();

		component = new double[length];
		for (int i = 0; i<length; i++)
			component[i] = V.component[i];
	}

	//Move constructor
	Vector(Vector &&V)
	{
		cout << "move constructor" << endl;
		length = V.length;
		component = V.component;
		V.component = nullptr; V.length = 0;
	}

	//Destructor
	~Vector(){ 
		delete component; }

	//Accessors:
	int getLength() const { return length; } // Return X cmpnt
	
	int index(int m) const // Return position in array of element (x,y,z)
	{
		if (m>0 && m <= length) return (m - 1);
		else { cout << "Error: out of range" << endl; exit(1); }
	}

	double & operator()(int m) {
		return component[index(m)]; }

	double & operator [](int n)const{
		if (n<1 || n>length){ cerr << "Error: out of range" << endl; exit(1); }
		return component[n-1];
	}

	//Overload Fucntions:

	//Copy Overload
	Vector & operator =(Vector &V)
	{
		if (&V == this) return*this; //no self assignment
		//First delete this objects array
		delete[] component; length = 0; component = nullptr;
		//now copy size and declare new array
		length = V.getLength();

		if (length>0)
		{
			component = new double[length];
			// Copy values into new array
			for (int i = 0; i<length; i++)
				component[i] = V.component[i];
		}
		return *this; // Special pointer
	}

	//Move Overload
	Vector & operator =(Vector&& V)
	{
		cout << "Move assignment" << endl;
		swap(length, V.length);
		swap(component, V.component);
		return*this;
	}

	//Member Function:
	//Dot product:
	double operator *(Vector& V)const{
		double product{ 0 };
		if (length != V.length){ cerr << "Error: The dimensions of the vector are invalid" << endl; exit(1); }
		for (int i{ 0 }; i < length; i++)
			product += V.component[i] * component[i];
		return product;
	}

};
//Derived class
class Minkowski : public Vector{
	//friend function:
	friend ostream& operator<<(ostream &os, const Minkowski &M);

public:
	//Default constructor
	Minkowski():
		Vector() {}

	//Parametised constructor (components)
	Minkowski(double _ct, double _x, double _y, double _z){
		length = 4; component = new double[length];
		component[0] = _ct; component[1] = _x; component[2] = _y; component[3] = _z;
	}

	//Parametised constructor (vector)
	Minkowski(double _ct, const Vector V) :
		Vector (4) {
		component = new double[length];
		component[0] = _ct;
		for (int i{ 1 }; i <= 3; i++)
			component[i] = V[i+1];
	}

	//Copy Constructor
	Minkowski(Minkowski const& M)
	{
		//deep copy mink
		cout << " deep copy Mink\n";
		component = nullptr; length = M.getLength();

		component = new double[length];
		for (int i = 0; i<length; i++)
			component[i] = M.component[i];
	}

	//Move Constructor
	Minkowski(Minkowski &&M)
	{
		cout << "move constructor" << endl;
		length = M.length;
		component = M.component;
		M.component = nullptr; M.length = 0;
	}

	//Destructor
	~Minkowski(){}

	//Accessors:
	//Get vector length
	int getLength() const { return length; } // Return X cmpnt

	//index
	int index(int m) const // Return position in array of element (x,y,z)
	{
		if (m>0 && m <= length) return (m - 1);
		else { cout << "Error: out of range" << endl; exit(1); }
	}
	//get components
	double & operator()(int m) { return component[index(m)]; }

	double & operator [](int n)const{
		if (n>1 || n <= length) return component[n - 1];
		else { cerr << "Error: out of range" << endl; exit(1); }
		
	}

	//Overload functions:
	//Copy Assignment
	Minkowski & operator =(Minkowski &M)
	{
		if (&M == this) return*this; //no self assignment
		//First delete this objects array
		delete[] component; length = 0; component = nullptr;
		//now copy size and declare new array
		length = M.getLength();

		if (length>0)
		{
			component = new double[length];
			// Copy values into new array
			for (int i = 0; i<length; i++)
				component[i] = M.component[i];
		}
		return *this; // Special pointer
	}
	
	//Move Assignment
	Minkowski & operator =(Minkowski&& M)
	{
		cout << "Move assignment" << endl;
		swap(length, M.length);
		swap(component, M.component);
		return*this;
	}

	//Overridden Function:
	//Dot product
	double operator *(Minkowski& M)const{
		double spatialProduct{ 0 }, product{ 0 };
		if (length != M.length){ cerr << "Error: The dimensions of the vector are invalid" << endl; exit(1); }
		for (int i{ 1 }; i < length; i++)
			spatialProduct += M.component[i] * component[i];
		return product = (M.component[0] * component[0]) - spatialProduct;
		
	}

	//Member funciton:
	//Lorents boosted(velocity parameter)
	//1) get gamma
	double getGamma(Vector& beta)
	{
		double gamma{ 0 }; double betaMod;
		betaMod = beta*beta;
		if (betaMod >= 1){ cerr << "Velocity out of limits."; exit(2); }
		gamma = 1 / sqrt(1 - pow(betaMod, 2));
		return gamma;
	}

	//2) time'
	double timeBoost(Vector& beta)
	{
		double time_prime{ 0 };
		double gamma = getGamma(beta);
		//Find way of accessing protected
		Vector temp(3);
		for (int i{ 1 }; i <= 3; i++){
			temp[i] = component[i];
		}
		
		time_prime = gamma * (component[0] - beta*temp);

		return time_prime;
	}

	//3) space'
	Minkowski Boost(Vector& beta)
	{
		Minkowski prime(0,4);
		double gamma = getGamma(beta);//exstract gamma
		//assign spatial vector of 4 vec to temp
		Vector temp(3);
		temp(1) = component[1]; temp(2) = component[2]; temp(3) = component[3];

		//get temporal boost
		double time_prime = timeBoost(beta);
		prime.component[0] = time_prime;

		//spatial program
		for (int i{ 1 }; i < 4; i++){
			prime.component[i] = temp(i) + ((gamma - 1) * (temp*beta) / (beta*beta) - (gamma*component[0]))*(beta[i]);
		}
		
		return prime;
	}

};

// Particle Class:

class particle{
private:
	Minkowski position;
	Vector beta;
	double mass;

public:
	//Default constructor
	particle() :
	beta(), mass(0), position(){}

	//Parametised constructor(mink  4vec, mass, beta 3 vec)
	particle(Minkowski _positions, Vector _beta, double _mass):
		position(_positions), beta(_beta) {	mass = _mass;}

	//Destructor
	~particle(){};

	//Member functions:
	//Calc gamma
	double getGamma(){
		double gamma{ 0 }; double betaMod;
		betaMod = beta*beta;
		if (betaMod >= 1){ cerr << "Velocity out of limits."; exit(2); }
		gamma = 1 / sqrt(1 - pow(betaMod, 2));
		return gamma;
	}

	//Calc momentum
	Vector getMomentum(){
		Vector Momentum(3);
		double gamma = getGamma();
		for (int i{ 1 }; i <= 3; i++){
			Momentum[i] = mass*gamma*beta[i];
		}
		return Momentum;
	}

	//Calc energy
	double getEnergy(){
		double gamma = getGamma();
		
		/*Vector Momentum = getMomentum();
		return sqrt(Momentum*Momentum + pow(mass,2));*/
		return gamma*mass;

	}

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////                           FRIENDS                          ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Overload insertion to output stream for matrices
ostream & operator<<(ostream &os, const Vector &V)
{
	//print size of Vector
	os << "\nVector size = (" << V.length << ")" << endl;

	//print Vector elements
	cout << "( ";
	for (int i{ 0 }; i < V.length; i++){
		cout << V.component[i] << "\t";
	}
	cout << " )" << endl;
	return os;
}

// // Overload insertion to output stream for Vector
ostream & operator<<(ostream &os,const Minkowski &M)
{
	//print size of Vector
	os << "\nMinkowski Vector size = (" << M.length<< ")" << endl;

	//print Vector elements
	cout << "(ct,x,y,z) = ( ";
	for (int i{ 0 }; i < M.length; i++){
		cout << M.component[i] << "\t";
	}
	cout << " )" << endl;
	return os;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////                           MAIN                          /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
#pragma region Section 1: Vector Class Test

	//Default constructor
	Vector a;
	cout << a << endl;
	//Define beta vector (using parametised constructor)
	Vector Beta(3);
	Beta(1) = 0.75; Beta(2) = 0; Beta(3) = 0;
	cout << Beta << endl;

	//Show vector copy overload
	Vector b(3);
	b(1) = 1; b(2) = 0; b(3) = 4;
	cout << "Vector B: " << b << endl;
	Vector c(3);
	cout << "Vector C: " << c << endl;
	c = b;
	cout << "Vector C: " << c << endl;
	// Modify contents of original vector (B) show assigned matrix (C) is unchanged
	b(1) = 2; b(2) = 6; b(3) = 0;
	cout << "Modified vector B: " << b;
	cout << "Assigned vector C: " << c;
	

	//Show vector move overload
	cout << "Move B to A assignment" << endl;
	a = move(b);
	cout << "vector A:" << a;
	cout << "vector B:" << b;

	//Show vector dot product
	cout << "Get the dot product of Vector A and Beta Vector:\n" << a*Beta << endl;
#pragma endregion Section 1: Vector Class Test

#pragma region Section 2: Derives Vector class: Minkowski 4 Vector
	
	//Default constructor
	Minkowski L;
	//Parametised constructor 1: (with vector)
	Minkowski F(3, Vector(4));
	F(1) = 1; F(2) = 2; F(3) = 2; F(4) = 5;
	cout << F << endl;
	
	//Parametised constructor 2: (with components)
	Minkowski G(5, 4, 2, 0);
	cout << G << endl;

	//Show vector copy overload
	Minkowski M(0,9,8,2);
	cout << "Vector M: " << M << endl;
	M = G;
	cout << "Vector M: " << M << endl;
	// Modify contents of original vector (G) show assigned matrix (M) is unchanged
	G(1) = 1; G(2) =0; G(3) = 1; G(4) = 1;
	cout << "Modified vector G: " << G;
	cout << "Assigned vector M: " << M;

	//Show vector move overload
	cout << "Move M to L (default) assignment" << endl;
	L = move(M);
	cout << "vector L:" << L;
	cout << "vector M:" << M;

	//Show minkowski vector dot product (over-ridden)
	cout << "Get the dot product of Vector L and G Vector:\n" << L*G << endl;

	//Lorents boost functions:
	//(1) get gamma
	cout << G.getGamma(Beta) << endl;
	//(2) get t'
	cout << G.timeBoost(Beta) << endl;
	//(3) get r'
	cout << G.Boost(Beta) << endl;
#pragma endregion

#pragma region	Section 3: Particle class

	//Parametised constructor (mink  Pos, Vec Beta, double Mass)
	Minkowski pos(5, 4, 2, 0); double Mass{ 10 };
	particle P1(pos, Beta, Mass);
	
	//Get gamma
	cout << "Print out gamma of particle: " << P1.getGamma() << endl;;
	//Get energy
	cout << "Print out P1 energy: " << P1.getEnergy() << endl;
	//Get momentum
	cout << "Print out P1 momentum vector: " << P1.getMomentum() << endl;
#pragma endregion
	return 0;
}