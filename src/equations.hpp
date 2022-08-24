#ifndef EQUATIONS_HEADER
#define EQUATIONS_HEADER

#include <math.h>

typedef enum 
{
    No = 0,
    One = 1,
    Two = 2,
    Infinity = 404
} RootsCount;

/// Solve equation: ax^2 + bx + c = 0
/// If equation has only one root, then only x1 contains value of the root!
/// @param[in] a first coefficient
/// @param[in] b second coefficient
/// @param[in] c third coefficient
/// @param[out] x1 first root
/// @param[out] x2 second root 
/// @return number of roots
RootsCount SolveEquation(double a, double b, double c, double *x1, double *x2);

/// Solve equation: ax + b = 0
/// @return number of roots
RootsCount SolveLinearEquation(double a, double b, double *x);

/// Solve equation: ax^2 + bx + c = 0
/// Where a is not equal to zero!
/// @return number of roots
RootsCount SolveQuadraticEquation(double a, double b, double c, double *x1, double *x2);

/// Check is |num| is less than 1e-7.
int IsTiny(double num);

#endif