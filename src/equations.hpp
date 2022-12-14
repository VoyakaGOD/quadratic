#ifndef EQUATIONS_HEADER
#define EQUATIONS_HEADER

#include <math.h>

const double double_epsilon = 1e-7;

typedef enum 
{
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = 404
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

/// Check is |num| is less than double_epsilon constant.
int IsTiny(double num);

#endif