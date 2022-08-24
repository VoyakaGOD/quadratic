#include "IOLib.hpp"
#include <time.h>

#define TEST_ASSERT(condition) if(!(condition)) *__success = 0;

#define PRINT(...) printf(__VA_ARGS__); if(LogFile != NULL) fprintf(LogFile, __VA_ARGS__)

FILE *LogFile = NULL;

/// A,B,C - coefficients of polynomial\n
/// RootsCount - expected number of roots\n
/// X1, X2 - expected roots
typedef struct 
{
    double A = NAN;
    double B = NAN;
    double C = NAN;
    RootsCount RootsCount = RootsCount::No;
    double X1 = NAN;
    double X2 = NAN;
} TestInfo;

/// Cute print of test result.
void PrintTestResult(int success)
{
    PRINT("---------------------------------------Result: %s!\n", success ?  "success[V]" : "fail[X]");
}

/// Compare A{a1, a2} and B{b1, b2} without order.
int IsSetsEqual(double a1, double a2, double b1, double b2)
{
    return (IsTiny(a1 - b1) && IsTiny(a2 - b2)) || (IsTiny(a1 - b2) && IsTiny(a2 - b1));
}

/// Is difference between a and b is tiny.
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

    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(a, b, c, &x1, &x2);

    double discriminant = b*b - 4*a*c;
    switch(rootsCount)
    {
        case RootsCount::No:
        {
            TEST_ASSERT(discriminant < 0);
            break;
        }
        case RootsCount::One:
        {    
            TEST_ASSERT(IsTiny(discriminant));
            TEST_ASSERT(IsTiny(a*x1*x1 + b*x1 + c));
            break;
        }
        case RootsCount::Two:
        {
            TEST_ASSERT(discriminant > 0);
            TEST_ASSERT(IsTiny(a*x1*x1 + b*x1 + c));
            TEST_ASSERT(IsTiny(a*x2*x2 + b*x2 + c));
            break;
        }
        case RootsCount::Infinity:
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
        double x1 = 0, x2 = 0;
        RootsCount rootsCount = SolveEquation(test.A, test.B, test.C, &x1, &x2);

        PRINT("Test %i:\n", i);
        DisplayEquation(test.A, test.B, test.C);
        PRINT("[roots count] expected %i, given %i\n", test.RootsCount, rootsCount);
        
        if(test.RootsCount != rootsCount)
        {
            PrintTestResult(0);
            continue;
        }

        switch(test.RootsCount)
        {
            case RootsCount::One:
            {
                PRINT("[x1] expected %lg, given %lg\n", test.X1, x1);
                PrintTestResult(IsClose(test.X1, x1));
                break;
            }
            case RootsCount::Two:
            {
                PRINT("[x1 x2] expected %lg %lg, given %lg %lg\n", test.X1, test.X2, x1, x2);
                PrintTestResult(IsSetsEqual(test.X1, test.X2, x1, x2));
                break;
            }
            default:
            {
                PrintTestResult(1);
                break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        LogFile = fopen(argv[1], "w");
    }

    PRINT("Standart tests:\n");
    TestInfo tests[] = { 
        {0, 0, 1,    RootsCount::No, 0, 0}, 
        {0, 0, 0,    RootsCount::Infinity, 0, 0}, 
        {0, 5, 25,   RootsCount::One, -5, 0},
        {1, 0, -36,  RootsCount::Two, 6, -6}, 
        {3, 12, 0,   RootsCount::Two, 0, -4}, 
        {10, 6, 0.9, RootsCount::One, -0.3, 0}
    };
    SolveEquationTestArray(tests, 6);

    PRINT("Random tests:\n");
    srand(time(NULL));
    for(int i = 0; i < 15; i++)
    {
        int success = 1;
        PRINT("test %d: start!\n", i);
        SolveEquationRandomTest(&success);
        PrintTestResult(success);
    }

    if(LogFile != NULL)
    {
        fclose(LogFile);
    }
    
    getchar();
}