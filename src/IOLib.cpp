#include "IOLib.hpp"

int IsDouble(char *string)
{
	assert(string != NULL);

	if (string[0] == 0)
		return 0;
	
	
	int i = 0;
	if (string[0] == '-')
	{
		if (string[1] == 0)
			return 0;
		i = 1;
	}

	int dot = 0;
	for(; string[i]; i++)
	{
		if (string[i] < '0' || string[i] > '9')
		{
			if(dot || string[i] != '.')
				return 0;
			else
				dot = 1;
		}
	}
	return 1;
}

void InputCoefficientsFromFile(FILE* file, double *a, double *b, double *c)
{
	assert(file != NULL);
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	assert(fscanf(file, "%lg", a) > 0);
	assert(fscanf(file, "%lg", b) > 0);
	assert(fscanf(file, "%lg", c) > 0);
	assert(getc(file) == EOF);
}

void InputCoefficientsFromStdin(double *a, double *b, double *c)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	printf("Enter coefficients of quadratic:");

	while(true)
	{
		scanf("%lg %lg %lg", a, b, c);
		if(getchar() == '\n')
		break;
		
		printf("Incorrect input data!\n");
	}
}

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
			assert(IsDouble(argv[1]));
			assert(IsDouble(argv[2]));
			assert(IsDouble(argv[3]));

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

void DisplayRoots(RootsCount rootsCount, double x1, double x2)
{
	switch(rootsCount)
	{
		case RootsCount::No:
		{
			printf("The quadratic has no roots!");
			break;
		}
		case RootsCount::One:
		{
			printf("The quadratic has one root: %lg!", x1);
			break;
		}
		case RootsCount::Two:
		{
			printf("The quadratic has two roots: %lg and %lg!", x1, x2);
			break;
		}
		case RootsCount::Infinity:
		{
			printf("The quadratic has infinity number of roots!");
			break;
		}
		default:
		{
			printf("Something is wrong!");
			break;
		}
	}
}

void DisplayEquation(double a, double b, double c)
{
	if(!IsTiny(a))
        printf("%lgx^2 + ", a);
    if(!IsTiny(b))
        printf("%lgx + ", b);
    printf("%lg = 0\n", c);
}

void WaitChar()
{
    fflush(stdin);
	getchar();
}