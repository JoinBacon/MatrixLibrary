#include "MatrixClass.h"

int main() 
{
	try
	{
		Matrix M;
		Matrix M1;
		EMatrix E(5);
		std::ifstream file("Rank.txt");
		if (file) {
			file >> M;
			file.close();
		}
		//std::cout << Tr(M) << std::endl;
	/*	std::ofstream f("dataload.txt", std::ios_base::app);
		if (!f.eof()) {
			f << M;
			f.close();
		}*/
		std::cout << M << std::endl;
		std::cout << Rank(M) << std::endl;
	/*	std::cout << Determinate(M) << std::endl;*/

		//M.BinaryWrite(M, "Matrix4.bin");
		//M1.BinaryRead(M1, "Matrix4.bin");
		//std::cout << M1 << std::endl;
		//std::cout << Transpose(M1) << std::endl;
	}
	catch (Exception1 e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}