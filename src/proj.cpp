#include "equations.hpp"
#include "IOLib.hpp"

int main()
{
	double a = 0, b = 0, c = 0;
	InputCoefficients(&a, &b, &c);

	double x1 = 0, x2 = 0;
	RootsCount rootsCount = SolveEquation(a, b, c, &x1, &x2);
	
	DisplayRoots(rootsCount, x1, x2);

	WaitChar();
	return 0;
}