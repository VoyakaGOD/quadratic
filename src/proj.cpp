/// \file
/// \brief It's main file!

#include "equations.hpp"
#include "my_assert.hpp"
#include <iostream>
#include "IOLib.hpp"
#include <stdlib.h>


int strcmp(char *left, const char *right)
{
	for(int i = 0; left[i] && right[i]; i++)
	{
		if(left[i] != right[i])
			return 0;
	}
	return 1;
}

/// Input coefficients taking into account args count and values.
/// If 2 args, then read data from file.
/// If 4 args, then read data from args.
/// Otherwise read data from stdin.
void InputCoefficients(double *a, double *b, double *c, int argc, char* argv[])
{
	switch(argc)
	{
		case 1:
		{
			InputCoefficientsFromStdin(a, b, c);
			break;
		}
		case 2:
		{
			if (strcmp(argv[1], "--help"))
			{
				printf("Possible args:\n");
				printf("[filename] - read data from file\n");
				printf("[a] [b] [c] - explicitly sets coefficients\n");
			}
			else
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
			}
			break;
		}
		case 4:
		{
			assert(IsDigit(argv[1]));
			assert(IsDigit(argv[2]));
			assert(IsDigit(argv[3]));

			*a = atof(argv[1]);
			*b = atof(argv[2]);
			*c = atof(argv[3]);
			break;
		}
		default:
		{
			printf("Incrorrect args count!");
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