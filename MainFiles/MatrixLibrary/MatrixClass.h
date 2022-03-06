#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

class Exception1 : public std::exception {
	std::string text;
public:
	Exception1(std::string str) : text(str) {};
	const char* what() const throw () {
		return text.c_str();
	}
};
class Matrix {
protected:
	int line;
	int column;
	std::vector <std::vector <double>> M;
public:
	Matrix();
	Matrix(int, int);
	Matrix(std::vector<std::vector<double>>);
	int GetLine() const;
	int GetCol() const;
	double& GetElem(const int, const int, const Matrix&);
	friend Matrix operator+(const Matrix&, const Matrix&);
	friend Matrix operator-(const Matrix&, const Matrix&);
	friend Matrix operator*(const Matrix&, const Matrix&);
	friend Matrix operator*(const Matrix&, const double);
	friend Matrix operator*(const double, const Matrix&);
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	friend std::ofstream& operator<<(std::ofstream&, Matrix&);
	friend std::ifstream& operator>>(std::ifstream&, Matrix&);
	void BinaryWrite(Matrix&, std::string) const;
	void BinaryRead(Matrix&, std::string);
};
Matrix HadamardProduct(Matrix c1, Matrix c2);
double Tr(Matrix c1);
double Determinate(Matrix c1);
double Scalar(Matrix c1, Matrix c2);
double EuclideanNorm(Matrix c1);
double MaximumNorm(Matrix c1);
double FrobeniusNorm(Matrix c1);
int Rank(Matrix c1);
double Angle(Matrix c1, Matrix c2);
Matrix ReverseM(Matrix c1);
Matrix Transpose(Matrix& c1);

class EMatrix : public Matrix {
public:
	EMatrix(int);
};

class DiagonalMatrix : public Matrix {
public:
	DiagonalMatrix(Matrix);
	DiagonalMatrix(int);
};

class UpperTriangular : public Matrix {
public:
	UpperTriangular(Matrix);
	UpperTriangular(int);
};

class LowerTriangular : public Matrix {
public:
	LowerTriangular(Matrix);
	LowerTriangular(int);
};

class SymmetricalMatrix : public Matrix {
public:
	SymmetricalMatrix(int);
};