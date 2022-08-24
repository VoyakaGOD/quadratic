/// \file
/// \brief It's main file!

#include "equations.hpp"
#include "IOLib.hpp"
#include <stdlib.h>

/// Input coefficients taking into account args count and values.
/// If 2 args, then read data from file.
/// If 4 args, then read data from args.
/// Otherwise read data from stdin.
void InputCoefficients(double *a, double *b, double *c, int argc, char* argv[])
{
	switch(argc)
	{
		case 2:
		{
			FILE *file;
			if ((file = fopen(argv[1], "r")) == NULL)
			{
				printf("Incorrect file!");
				WaitChar();
				return;
			}
			InputCoefficientsFromFile(file, a, b, c);
			fclose(file);
			break;
		}
		case 4:
		{
			*a = atof(argv[1]);
			*b = atof(argv[2]);
			*c = atof(argv[3]);
			break;
		}
		default:
		{
			InputCoefficientsFromStdin(a, b, c);
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	double a = 0, b = 0, c = 0;
	InputCoefficients(&a, &b, &c, argc, argv);

	double x1 = 0, x2 = 0;
	RootsCount rootsCount = SolveEquation(a, b, c, &x1, &x2);
	
	DisplayEquation(a, b, c);
	DisplayRoots(rootsCount, x1, x2);

	WaitChar();
	return 0;
}