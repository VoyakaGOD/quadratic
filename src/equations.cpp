#include "equations.hpp"
#include "my_assert.hpp"

int IsTiny(double num)
{
    return fabs(num) < double_epsilon;
}

static RootsCount SolveQuadraticEquation(double a, double b, double c, double *x1, double *x2)
{
    assert(!IsTiny(a));

    if (IsTiny(c))
	{
		*x1 = 0;
		*x2 = -b/a;
		return (IsTiny(b)) ? ONE_ROOT : TWO_ROOTS;
    }

	double D = b*b - 4*a*c;
	if (IsTiny(D))
	{
		*x1 = -0.5 * b / a;
		return ONE_ROOT;
	}
	if (D < 0)
	{
		return NO_ROOTS;
	}
	
	double sqrtD = sqrt(D);
	double denominator = 1 / (2*a);
	*x1 = denominator * (-b + sqrtD);
	*x2 = denominator * (-b - sqrtD);
	return TWO_ROOTS;
}

RootsCount SolveLinearEquation(double a, double b, double *x)
{
	assert(!isnan(a) && !isnan(b));
	assert(isfinite(a) && isfinite(b));
	assert(x != NULL);

    if(IsTiny(a))
		return IsTiny(b) ? INF_ROOTS : NO_ROOTS;
	*x = -b/a;
	return ONE_ROOT;
}

RootsCount SolveEquation(double a, double b, double c, double *x1, double *x2)
{
	assert(!isnan(a) && !isnan(b) && !isnan(c));
	assert(isfinite(a) && isfinite(b) && isfinite(c));
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	if (IsTiny(a))
        return SolveLinearEquation(b, c, x1);
	else
		return SolveQuadraticEquation(a, b, c, x1, x2);
}