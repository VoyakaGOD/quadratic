#include "TestLib.hpp"
#include "IOLib.hpp"
#include <time.h>

#define RANDOM_TEST_COUNT 15

#define TEST_ASSERT(condition) if(!(condition)) *__success = 0;

/// A,B,C - coefficients of polynomial\n
/// RootsCount - expected number of roots\n
/// X1, X2 - expected roots
typedef struct 
{
    double A = NAN;
    double B = NAN;
    double C = NAN;
    RootsCount RootsCount = No;
    double X1 = NAN;
    double X2 = NAN;
} TestInfo;

/// @param[in] e1 first expected root
/// @param[in] e2 second expected root
/// @param[in] g1 first given root
/// @param[in] g2 second given root
int IsRootsEqual(double e1, double e2, double g1, double g2)
{
    return (IsTiny(a1 - b1) && IsTiny(a2 - b2)) || (IsTiny(a1 - b2) && IsTiny(a2 - b1));
}

/// Is difference between a and b is less than 1e-7.
int IsClose(double a, double b)
{
    return IsTiny(a - b);
}

/// Test SolveEquation function with random parameters.
void SolveEquationRandomTest(int *__success)
{
    double a = rand() % 2001 - 1000;
    double b = rand() % 2001 - 1000;
    double c = rand() % 2001 - 1000;

    double x1 = NAN, x2 = NAN;
    RootsCount rootsCount = SolveEquation(a, b, c, &x1, &x2);

    double discriminant = b*b - 4*a*c;
    switch(rootsCount)
    {
        case No:
        {
            TEST_ASSERT(discriminant < 0);
            break;
        }
        case One:
        {    
            TEST_ASSERT(IsTiny(discriminant));
            TEST_ASSERT(IsTiny(a*x1*x1 + b*x1 + c));
            break;
        }
        case Two:
        {
            TEST_ASSERT(discriminant > 0);
            TEST_ASSERT(IsTiny(a*x1*x1 + b*x1 + c));
            TEST_ASSERT(IsTiny(a*x2*x2 + b*x2 + c));
            break;
        }
        case Infinity:
        {
            TEST_ASSERT(IsTiny(a) && IsTiny(a) && IsTiny(c));
            break;
        }
    }

    if(!(*__success))
    {
        PRINT("%lgx^2 + %lgx + %lg = 0", a, b, c);
        PRINT("x1 = %lg", x1);
        PRINT("x2 = %lg", x2);
    }
}

/// Test SolveEquation function with parameters specified by TestInfo for each element of tests array.
void SolveEquationTestArray(TestInfo *tests, int count)
{
    for(int i = 0; i < count; i++)
    {
        TestInfo test = tests[i];
        double x1 = NAN, x2 = NAN;
        RootsCount rootsCount = SolveEquation(test.A, test.B, test.C, &x1, &x2);

        PRINT("Test %i:\n", i);
        
        if(test.RootsCount == rootsCount && IsRootsEqual(test.X1, test.X2, x1, x2))
        {
            PrintTestResult(1);
            continue;
        }

        DisplayEquation(test.A, test.B, test.C);
        PRINT("[roots count] expected %i, given %i\n", test.RootsCount, rootsCount);
        switch(test.RootsCount)
        {
            case One:
            {
                PRINT("[x1] expected %lg, given %lg\n", test.X1, x1);
                break;
            }
            case Two:
            {
                PRINT("[x1 x2] expected %lg %lg, given %lg %lg\n", test.X1, test.X2, x1, x2);
                break;
            }
        }
        PrintTestResult(0);
    }
}

int main(int argc, char* argv[])
{
    if (argc == 2)
        OpenLogFile(argv[1]);

    PRINT("Standart tests:\n");
    TestInfo tests[] = { 
        {0,  0,  1,    No,       NAN,    NAN}, 
        {0,  0,  0,    Infinity, NAN,    NAN}, 
        {0,  5,  25,   One,      -5,   NAN},
        {1,  0,  -36,  Two,      6,    -6}, 
        {3,  12, 0,    Two,      0,    -4}, 
        {10, 6,  0.9,  One,      -0.3, NAN}
    };
    SolveEquationTestArray(tests, 6);

    PRINT("Random tests:\n");
    srand(time(NULL));
    for(int i = 0; i < RANDOM_TEST_COUNT; i++)
    {
        int success = 1;
        PRINT("test %d: start!\n", i);
        SolveEquationRandomTest(&success);
        PrintTestResult(success);
    }

    CloseLogFile();
    
    getchar();
}