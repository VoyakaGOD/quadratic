#include "IOLib.hpp"
#include <iostream>
#include <assert.h>

void InputCoefficients(double *a, double *b, double *c)
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
			printf("The quadratic has no roots!");
			break;
		case RootsCount::One:
			printf("The quadratic has one root: %lg!", x1);
			break;
		case RootsCount::Two:
			printf("The quadratic has two roots: %lg and %lg!", x1, x2);
			break;
		case RootsCount::Infinity:
			printf("The quadratic has infinity number of roots!");
			break;
		default:
			printf("Something is wrong!");
			break;
	}
}

void WaitChar()
{
    fflush(stdin);
	getchar();
}