#ifndef IOLIB_HEADER
#define IOLIB_HEADER

#include "equations.hpp"

/// Input the coeffitients values.
/// @param[out] a first coefficient
/// @param[out] b second coefficient
/// @param[out] c third coefficient
void InputCoefficients(double *a, double *b, double *c);

/// Cute display of roots.
void DisplayRoots(RootsCount rootsCount, double x1, double x2);

void WaitChar();

#endif