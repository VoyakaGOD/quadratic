#ifndef IOLIB_HEADER
#define IOLIB_HEADER

#include "equations.hpp"
#include <stdio.h>

/// Input the coeffitients values from file.
/// @param[in] file file from which we get data
/// @param[out] a first coefficient
/// @param[out] b second coefficient
/// @param[out] c third coefficient
void InputCoefficientsFromFile(FILE* file, double *a, double *b, double *c);

/// Input the coeffitients values from stdin stream.
/// @param[out] a first coefficient
/// @param[out] b second coefficient
/// @param[out] c third coefficient
void InputCoefficientsFromStdin(double *a, double *b, double *c);

/// Cute display of roots.
void DisplayRoots(RootsCount rootsCount, double x1, double x2);

/// Cute display of equation.
void DisplayEquation(double a, double b, double c);

/// Clear stdin and wait next char
void WaitChar();

#endif