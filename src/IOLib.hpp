#ifndef IOLIB_HEADER
#define IOLIB_HEADER

#include <string.h>
#include "my_assert.hpp"
#include "equations.hpp"

/// Check is the string contains only digits, dot and maybe sign.
int IsDouble(char *string);

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

/// Input coefficients taking into account command line args count and values.
/// If 2 args, then read data from file.
/// If 4 args, then read data from args.
/// Otherwise read data from stdin.
void InputCoefficients(double *a, double *b, double *c, int argc, char* argv[]);

/// Cute display of roots.
void DisplayRoots(RootsCount rootsCount, double x1, double x2);

/// Cute display of equation.
void DisplayEquation(double a, double b, double c);

/// Clear stdin and wait next char
void WaitChar();

#endif