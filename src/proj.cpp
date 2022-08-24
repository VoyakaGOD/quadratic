/// \file
/// \brief It's main file!

#include "IOLib.hpp"

int main(int argc, char* argv[])
{
	if (argc == 2 && !strcmp(argv[1], "--help"))
	{
		printf("Possible args:\n");
		printf("[filename] - read data from file\n");
		printf("[a] [b] [c] - explicitly sets coefficients\n");
		return 0;
	}

	double a = NAN, b = NAN, c = NAN;
	InputCoefficients(&a, &b, &c, argc, argv);

	double x1 = NAN, x2 = NAN;
	RootsCount rootsCount = SolveEquation(a, b, c, &x1, &x2);
	
	DisplayEquation(a, b, c);
	DisplayRoots(rootsCount, x1, x2);

	WaitChar();
	return 0;
}