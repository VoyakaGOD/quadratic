#include "IOLib.hpp"
#include <iostream>
#include "my_assert.hpp"

void InputCoefficientsFromFile(FILE* file, double *a, double *b, double *c)
{
	assert(file != NULL);
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	assert(fscanf(file, "%lg", a) != 0);
	assert(fscanf(file, "%lg", b) != 0);
	assert(fscanf(file, "%lg", c) != 0);
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