#include "equations.hpp"
#include "my_assert.hpp"

int IsTiny(double num)
{
    return abs(num) < 1e-7;
}

RootsCount SolveEquation(double a, double b, double c, double *x1, double *x2)
{
	assert(!isnan(a));
	assert(!isnan(b));
	assert(!isnan(c));
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
	assert(!isnan(a));
	assert(!isnan(b));
	assert(isfinite(a));
	assert(isfinite(b));
	assert(x != NULL);

    if(IsTiny(a))
		return IsTiny(b) ? Infinity : No;
	*x = -b/a;
	return One;
}

RootsCount SolveQuadraticEquation(double a, double b, double c, double *x1, double *x2)
{
	assert(!isnan(a));
	assert(!isnan(b));
	assert(!isnan(c));
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);
    assert(!IsTiny(a));

    if (IsTiny(c))
	{
		*x1 = 0;
		*x2 = -b/a;
		return (IsTiny(b)) ? One : Two;
    }

	double D = b*b - 4*a*c;
	if (IsTiny(D))
	{
		*x1 = -0.5 * b / a;
		return One;
	}
	if (D < 0)
	{
		return No;
	}
	
	double sqrtD = sqrt(D);
	double denominator = 1 / (2*a);
	*x1 = denominator * (-b + sqrtD);
	*x2 = denominator * (-b - sqrtD);
	return Two;
}