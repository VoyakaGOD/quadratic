#include "equations.hpp"
#include <assert.h>
#include <math.h>

#define BIG_EPSILON 1e-7
#define NULL 0

int IsTiny(double num)
{
    return abs(num) < BIG_EPSILON;
}

RootsCount SolveEquation(double a, double b, double c, double *x1, double *x2)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	if (IsTiny(a))
        return SolveLinearEquation(b, c, x1);
	else
		return SolveQuadraticEquation(a, b, c, x1, x2);
}

RootsCount SolveLinearEquation(double a, double b, double *x)
{
    if(IsTiny(a))
		return IsTiny(b) ? RootsCount::Infinity : RootsCount::No;
	*x = -b/a;
	return RootsCount::One;
}

RootsCount SolveQuadraticEquation(double a, double b, double c, double *x1, double *x2)
{
    assert(!IsTiny(a));

    if (IsTiny(c))
	{
		*x1 = 0;
		*x2 = -b/a;
		return (IsTiny(b)) ? RootsCount::One : RootsCount::Two;
    }

	double D = b*b - 4*a*c;
	if (IsTiny(D))
	{
		*x1 = -0.5 * b / a;
		return RootsCount::One;
	}
	if (D < 0)
	{
		return RootsCount::No;
	}
	
	double sqrtD = sqrt(D);
	double denominator = 1 / (2*a);
	*x1 = denominator * (-b + sqrtD);
	*x2 = denominator * (-b - sqrtD);
	return RootsCount::Two;
}