#include "MatrixClass.h"

Matrix::Matrix():
	line(0), column(0)
{

}

Matrix::Matrix(int m = 5, int n = 5):
	line(m), column(n)
{
	M.resize(line, std::vector<double>(column));
}

Matrix::Matrix(std::vector<std::vector<double>> vals) {
	for (int i = 0; (unsigned)i < vals.size(); i++) {
		if (vals[0].size() != vals[i].size()) {
			throw Exception1("Error");
		}
	}
	line = vals.size();
	column = vals[0].size();
	M = vals;
}
int Matrix::GetLine() const{
	return line;
}

int Matrix::GetCol() const{
	return column;
}

double& Matrix::GetElem(const int i, const int j, const Matrix& c1){
	return M[i][j];
}

Matrix operator+(const Matrix& c1, const Matrix& c2) {
	
	if (c1.line != c2.line || c1.column != c2.column) {
		throw Exception1("Error: the matrices have different sizes.");
	}
	Matrix Sum(c1.line, c1.column);
	for (int i = 0; i < c1.line; ++i) {
		for (int j = 0; j < c1.column; ++j) {
			Sum.M[i][j] = c1.M[i][j] + c2.M[i][j];
		}
	}
	return Sum;
}

Matrix operator-(const Matrix& c1, const Matrix& c2) {
	if (c1.line != c2.line || c1.column != c2.column) {
		throw Exception1("Error: the matrices have different sizes.");
	}
	Matrix Dif(c1.line, c1.column);
	for (int i = 0; i < c1.line; ++i) {
		for (int j = 0; j < c1.column; ++j) {
			Dif.M[i][j] = c1.M[i][j] - c2.M[i][j];
		}
	}
	return Dif;
}

Matrix operator*(const Matrix& c1, const Matrix& c2){
	if (c1.column != c2.line) {
		throw Exception1("Error: the matrices have different sizes.");
	}
	Matrix Res(c1.line, c2.column);
	for (int i = 0; i < c1.line; ++i) {
		for (int j = 0; j < c2.column; ++j) {
			for (int l = 0; l < c1.column; ++l) {
				Res.M[i][j] += c1.M[i][l] * c2.M[l][j];
			}
		}
	}
	return Res;
}

Matrix operator*(const Matrix& c1, const double value) {
	Matrix Res(c1.line, c1.column);
	for (int i = 0; i < c1.line; ++i) {
		for (int j = 0; j < c1.column; ++j) {
			Res.M[i][j] = c1.M[i][j] * value;
		}
	}
	return Res;
}

Matrix operator*(const double value, const Matrix& c1) {
	Matrix Res(c1.line, c1.column);
	for (int i = 0; i < c1.line; ++i) {
		for (int j = 0; j < c1.column; ++j) {
			Res.M[i][j] = value * c1.M[i][j];
		}
	}
	return Res;
}


std::ostream& operator<<(std::ostream& ostr, const Matrix& c1) {
	for (int i = 0; i < c1.line; ++i)
	{
		for (int j = 0; j < c1.column; ++j) {
			ostr << c1.M[i][j] /*<< ostr.precision(3)*/ <<"\t";
		}
		ostr << "\n";
	}
	return(ostr);
}
std::ofstream& operator<<(std::ofstream& f, Matrix& c1) {
	for (int i = 0; i < c1.line; ++i) {
		for (int j = 0; j < c1.column; ++j) {
			f << c1.M[i][j] << "\t";
		}
		f << "\n";
	}
	return f;
}

std::ifstream& operator>>(std::ifstream& f, Matrix& c1) {
	std::vector<double> values;
	int columns = 0, lines = 0;
	double a;
	while (f >> a) {
		values.push_back(a);
		if (f.peek() == '\n' || f.peek() == EOF)
		{
			if (columns != 0 && columns != values.size()) {
				throw Exception1("Error: the different shapes of lines in matrix");
			}
			++lines;
			columns = values.size();
			c1.M.push_back(values);
			values.clear();
		}
	}
	c1.line = lines;
	c1.column = columns;
	return f;
}

void Matrix::BinaryWrite(Matrix& c1, std::string NameFile) const{
	std::ofstream file(NameFile, std::ios::binary | std::ios::app | std::ios_base::app);
	if (!file) {
		throw Exception1("file open error");
	}
	int lines = c1.GetCol();
	int columns = c1.GetCol();
	file.write((char*)&lines, sizeof(int));
	file.write((char*)&columns, sizeof(int));
	for (int i = 0; i < c1.GetLine(); ++i) {
		for (int j = 0; j < c1.GetCol(); ++j) {
			file.write((char*)&c1.M[i][j], sizeof(double));
		}
	}
	file.close();
}
void Matrix::BinaryRead(Matrix& c1, std::string NameFile) {
	std::ifstream f(NameFile, std::ios::binary | std::ios_base::app);
	f.read((char*)&c1.line, sizeof(int));
	f.read((char*)&c1.column, sizeof(int));
	c1.M.resize(c1.line, std::vector<double>(c1.column));
	if (!f) {
		throw Exception1("file open error");
	}
	else {
		for (int i = 0; i < c1.line; ++i) {
			for (int j = 0; j < c1.column; ++j) {
				f.read((char*)&c1.M[i][j], sizeof(double));
			}
		}
	}
	f.close();
}
EMatrix::EMatrix(int m):
	Matrix(m, m)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i == j)
				M[i][j] = 1;
			else
				M[i][j] = 0;
		}
	}
}


DiagonalMatrix::DiagonalMatrix(Matrix c1):
	Matrix(c1.GetLine(), c1.GetLine())
{
	if (c1.GetLine() != c1.GetCol()) {
		throw Exception1("diagonal: matrix must be square");
	}
	for (int i = 0; i < c1.GetLine(); ++i) {
		for (int j = 0; j < c1.GetLine(); ++j) {
			if (i == j) {
				M[i][j] = c1.GetElem(i, j, c1);
			}
			else {
				M[i][j] = 0;
			}
		}
	}

}
DiagonalMatrix::DiagonalMatrix(int m):
	Matrix(m, m)
{

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i == j) {
				M[i][j] = (double)(rand() % 10000) / 1000;
			}
			else {
				M[i][j] = 0;
			}
		}
	}
}
UpperTriangular::UpperTriangular(Matrix c1) :
	Matrix(c1.GetLine(), c1.GetLine())
{
	if (c1.GetLine() != c1.GetCol()) {
		throw Exception1("upper triangle: matrix must be square");
	}
	for (int i = 0; i < c1.GetLine(); ++i) {
		for (int j = 0; j < c1.GetLine(); ++j) {
			if (i >= j) {
				M[i][j] = c1.GetElem(i, j, c1);
			}
			else {
				M[i][j] = 0;
			}
		}
	}
}

UpperTriangular::UpperTriangular(int m) :
	Matrix(m, m)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i >= j) {
				M[i][j] = (double)(rand() % 10000) / 1000;
			}
			else {
				M[i][j] = 0;
			}
		}
	}
}

LowerTriangular::LowerTriangular(Matrix c1):
	Matrix(c1.GetLine(), c1.GetLine())
{
	if (c1.GetLine() != c1.GetCol()) {
		throw Exception1("upper triangle: matrix must be square");
	}
	for (int i = 0; i < c1.GetLine(); ++i) {
		for (int j = 0; j < c1.GetLine(); ++j) {
			if (i <= j) {
				M[i][j] = c1.GetElem(i, j, c1);
			}
			else {
				M[i][j] = 0;
			}
		}
	}
}
LowerTriangular::LowerTriangular(int m) :
	Matrix(m, m)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i <= j) {
				M[i][j] = (double)(rand() % 10000) / 1000;
			}
			else {
				M[i][j] = 0;
			}
		}
	}
}
SymmetricalMatrix::SymmetricalMatrix(int m) :
	Matrix(m, m)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (j >= i) {
				M[i][j] = (double)(rand() % 10000) / 1000;
			}
			else {
				M[i][j] = M[j][i];
			}
		}
	}
}
