#ifndef TEST_INFO_HEADR
#define TEST_INFO_HEADR

#include "equations.hpp"

/// A,B,C - coefficients of polynomial\n
/// RootsCount - expected number of roots\n
/// X1, X2 - expected roots
typedef struct 
{
    double A = NAN;
    double B = NAN;
    double C = NAN;
    RootsCount RootsCount = NO_ROOTS;
    double X1 = NAN;
    double X2 = NAN;
} TestInfo;

#endif