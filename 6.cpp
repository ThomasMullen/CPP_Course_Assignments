//#include"stdafx.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////                         Assignment 6 Matrix Class                            //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//HELP:
// copy constructor need to set parametised constructor array to 0 i think

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////             Description                            ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//produce a matrix class that can store (n X m) matrix data via dynamical memory
//nth and mth element of matrix can be located
//Assignment operator and copy constructor functions can perform deep copies of data
//Parameterized constructor (utilizing new) and destructor(utilizing delete)
//Member function to overload assignment operator that performs a deep copy of data. Must also handle self - assignment
//Use of move constructor and move assignment
//Friend function to overload cin and cout
//operate on matrices '+' '-' '*' (tests if it is possible)
//A member function to return a matrix with the ith row and jth column deleted
//A function to calculate recursively the determinant of a square matrix

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////                Headers                            //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Headers
#include<iostream>
#include<limits>
#include<cmath>
#include<stdlib.h> // for c style exit
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////                Matrix class                            //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class matrix
{
	// Friends
	friend ostream & operator<<(ostream &os, const matrix &M);
	friend istream & operator>>(istream &is, matrix &M);
private:
	double *mdata;
	int rows, columns;
public:

	matrix(); //Default Constructor
	// Parameterized constructor
	matrix(int _rows, int _columns);
	// Copy constructor
	matrix(matrix const& M);
	// Move constructor
	matrix(matrix &&M);

	// Destructor
	~matrix();
	// Access functions
	int getrows() const { return rows; } // Return number of rows
	int getcols() const { return columns; } // Return number of columns
	int index(int m, int n) const // Return position in array of element (m,n)
	{
		if (m>0 && m <= rows && n>0 && n <= columns) return (n - 1) + (m - 1) * columns;
		else { cout << "Error: out of range" << endl; exit(1); }
	}
	double & operator()(int m, int n) { return mdata[index(m, n)]; }
	// Other access functions go here

	// Other functions
	// Copy  Assignment operator
	matrix& operator=(matrix & M);
	// Move Assignment operator
	matrix& operator=(matrix &&M);

	// Addition, subtraction and multiplication:
	matrix operator+(matrix& M)const;

	matrix operator-(matrix& M)const;

	matrix operator*(matrix& M)const;

	// minor
	matrix getMinor(int rowRm, int colRm);

	// determinant
	double getDeterminant();

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////                 Defined Constructors & Assignments                //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Constructors Defined:

//Default constructor
matrix::matrix() :
mdata(nullptr), rows(0), columns(0){}

//Parameterised constructor
matrix::matrix(int _rows, int _columns){
	rows = _rows; columns = _columns; mdata = new double[_rows*_columns];
	//default matrix fill
	for (int i{ 0 }; i < rows*columns; i++){
		mdata[i] = 0;
	}
}
//Copy constructor
matrix::matrix(matrix const& M)
{
	//deep copy
	cout << " deep copy\n";
	mdata = nullptr; rows = M.getrows(); columns = M.getcols();

	if (rows > 0 || columns > 0){
		mdata = new double[(M.columns)*(M.rows)];
		for (int i = 0; i<M.columns*M.rows; i++)
			mdata[i] = M.mdata[i];
	}
}

//Move constructor
matrix::matrix(matrix &&M)
{
	cout << "move constructor" << endl;
	rows = M.rows; columns = M.columns;
	mdata = M.mdata;
	M.mdata = nullptr; M.rows = 0; M.columns = 0;
}

//Destructor
matrix::~matrix(){
	cout << "Deleting Data" << endl;
	columns = 0; rows = 0;
	delete[] mdata;
}

// Copy Assignment overload operator
matrix & matrix::operator =(matrix &M)
{
	if (&M == this) return*this; //no self assignment
	//First delete this objects array
	delete[] mdata; mdata = nullptr; columns = 0; rows = 0;
	//now copy size and declare new array
	columns = M.getcols();
	rows = M.getrows();
	if (rows>0 || columns>0)
	{
		mdata = new double[(columns)*(rows)];
		// Copy values into new array
		for (int i = 0; i<columns*rows; i++)
			mdata[i] = M.mdata[i];
	}
	return *this; // Special pointer
}

// Move Assignment Operator
matrix & matrix::operator=(matrix&& M)
{
	cout << "Move assignment" << endl;
	swap(columns, M.columns);
	swap(rows, M.rows);
	swap(mdata, M.mdata);
	return*this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////                           Matrix Operations                //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
matrix matrix :: operator-(matrix& M)const{
	//copy a temp matrix you want to operate on
	matrix temp; temp = M;
	for (int i = 0; i<temp.rows*temp.columns; i++)
		temp.mdata[i] -= this->mdata[i];
	return temp;
}

matrix matrix :: operator+(matrix& M)const{
	//copy a temp matrix you want to operate on
	matrix temp; temp = M;
	for (int i = 0; i<temp.rows*temp.columns; i++)
		temp.mdata[i] += this->mdata[i];
	return temp;
}

matrix matrix :: operator*(matrix& M)const{
	//copy a temp matrix you to operator on
	//A * B = C
	//A = M; B = this
	matrix temp(this->rows, M.columns);

	if (this->columns != M.rows){
		cerr << "Invalid operation" << endl;
		exit(2);
	}
	else{
		for (int i{ 0 }; i < this->rows; i++){
			for (int j{ 0 }; j < M.columns; j++){
				double sum{ 0 };
				for (int k{ 0 }; k < M.rows; k++){
					sum += this->mdata[(i * (this->columns)) + k] * M.mdata[(k * (M.columns)) + j];
				}
				temp.mdata[i * (temp.columns) + j] = sum;
			}
		}
	}
	return temp;
}

// Get minor function defined:
matrix matrix::getMinor(int rowRm, int colRm){
	int count{ 0 }; //minor element allocator
	matrix temp(rows - 1, columns - 1); //define size of minor

	for (int i{ 0 }; i < rows; i++){
		for (int j{ 0 }; j < columns; j++){
			//elements that are not in the removed row and column
			if (i != rowRm && j != colRm){
				temp.mdata[count] = this->mdata[i*columns + j];
				count++;
			}}}

//	cout << "\nThe Minor of this matrix is" << " (" << temp.columns << " x "<< temp.rows <<"):\n" << temp <<endl;
	return temp;
}

// Determinant defined
double matrix::getDeterminant(){
	double determinant{ 0 };
	matrix minor;
	if (rows != columns){ cerr << "Invalid operation." << endl; exit(3); }

	else if (rows == 2){
		return mdata[0] * mdata[3] - mdata[1] * mdata[2];
	}

	for (int i{ 0 }; i < columns; i++){
		minor = this->getMinor(0, i);
		determinant += mdata[i] * pow(-1, i) * minor.getDeterminant();
	}
	//cout << determinant << endl;
	return determinant;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////                           FRIENDS                          ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Overload insertion to output stream for matrices
ostream & operator<<(ostream &os, const matrix &M)
{
	//print dimension of matrix
	os << "\nMatrix m x n = (" << M.rows << " x " << M.columns << ")" << endl;

	//print matrix elements
	for (int i{ 0 }; i < M.rows; i++){
		for (int j{ 0 }; j < M.columns; j++){
			int loc = (j)+(i*M.columns);
			cout << M.mdata[loc] << "\t";
		}
		cout << endl; //after each row element of that colum has been access give a new line
	}
	cout << endl;
	return os;
}

// Overload insertion to input stream for matrices
istream & operator>>(istream& is, matrix& M)
{
	cout << "Please enter the column: ";
	is >> M.columns;
	cout << "Pleas enter the rows: ";
	is >> M.rows;

	//Matrix temp(M.columns, M.rows);
	M.mdata = new double[M.rows*M.columns];//assign M's 1d array size from prev. inputs

	//Assign matrix element values
	cout << "Please Enter th elements of your matrix from A_11 to A_nm:" << endl;
	for (int i{ 0 }; i < M.columns * M.rows; i++){
		cin >> M.mdata[i];
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	//Print out input matrix
	cout << M << endl;
	return is;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////                           MAIN                          /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Main program
int main()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////             Section 1: Constructing and Deep Copying              ///////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Demonstrate default constructor
	cout << "Demonstrate default constructor" << endl;
	matrix a1;
	cout << "Default matrix a1:" << a1;

	// Parameterized constructor
	const int m(2), n(2);
	matrix a2(m,n);
	
	// Set values for a2 here
	a2(1, 1) = 2; a2(1, 2) = 3;
	a2(2, 1) = 1; a2(2, 2) = 5;
	
	// Print matrix a2
	cout << "Demonstrate parameterized constructor" << endl;
	cout <<"Matrix a2:" << a2;
	
	// Deep copy by assignment: define new matrix a3 then copy from a2 to a3
	cout << "Demonstrate deep copy. Copy a2 to a3" << endl;
	matrix a3(m, n);
	cout << "Matrix a3 before copy:" << a3;
	a3 = a2;
	cout << "Matrix a3 after a2 copy:" << a3;

	// Modify contents of original matrix (a2) show assigned matrix (a3) is unchanged
	a2(1, 1) = 6; a2(1, 2) = 1;
	a2(2, 1) = 6; a2(2, 2) = 0;

	cout << "Modified matrix a2:" << a2;
	cout << "Assigned matrix a3:" << a3;


	// Deep copy using copy constructor 
	cout << "Demonstrate deep copy using constructor" << endl;
	matrix a4(a2);
	cout << "Copied matrix a4:" << a4;

	// Modify contents of original matrix and show copied matrix is unchanged here
	cout << "Matrix a2:" << a2;
	cout << "Matrix a4:" << a4;

	// Move assignment demonstration
	cout << "Demonstrate move assignment constructor" << endl;
	matrix a5;
	
	cout << "Move a3 to (default) a5 assignment" << endl;
	a5 = move(a3);
	cout << "Matrix a5:" << a5;
	cout << "Matrix a3:" << a3;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////             Section 2: Matrix Operations              ///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	matrix b0, b1, b2, min;
	
	//Addition, Subtraction, Multiplication
	cout << "We will show the matrix operations:\n(1) b0 + b1\n(2) b0 - b1\n(3) b0 * b1\nN.B. b0 columns need to be equal to b1 rows." << endl;
	cout << "Please enter b0:" << endl;
	cin >> b0;
	cout << "Please enter b0:" << endl;
	cin >> b1;
	cout << "(1)" << b0 + b1 << "(2)" << b0 - b1 << "(3)" << b0*b1 << endl;

	//Find Minor and get Determinant
	cout << "The determinant of b2 will be calculated.\nPlease enter b2:" << endl;
	cin >> b2;
	cout << "The first order minor of b2, M_11 is:" << endl;
	min = b2.getMinor(0, 0);
	cout << min << endl;

	double determinant = b2.getDeterminant();
	cout << "The Determinant of b2: " << determinant << endl;

	return 0;
}
/*Exit Codes:
(1): element of array out of range
(2): invalid dimensions of matrix for multiplication
(3): Matrix not square there unable to find determinant*/
