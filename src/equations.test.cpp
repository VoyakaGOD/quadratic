#include "equations.hpp"
#include "IOLib.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int NumberOfTest = 1;
int IsTestFailed = 0;

/// A,B,C - coefficients of polynomial\n
/// RootsCount - expected number of roots\n
/// X1, X2 - expected roots
typedef struct 
{
    double A;
    double B;
    double C;
    RootsCount RootsCount;
    double X1;
    double X2;
} TestInfo;

/// Rejects the test.
void Assert(int condition)
{
    if(condition)
        return;
    IsTestFailed = 1;
}

/// Cute print of test result.
void PrintTestResult(int success)
{
    printf("---------------------------------------Result: %s!\n", success ?  "success[V]" : "fail[X]");
}

/// Run the test and show result.
void Run(void (*test)())
{
    IsTestFailed = 0;
    printf("test %i: start!\n", NumberOfTest);
    test();
    PrintTestResult(!IsTestFailed);
    NumberOfTest++;
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
void SolveEquationRandomTest()
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
            Assert(discriminant < 0);
            break;
        }
        case RootsCount::One:
        {    
            Assert(IsTiny(discriminant));
            Assert(IsTiny(a*x1*x1 + b*x1 + c));
            break;
        }
        case RootsCount::Two:
        {
            Assert(discriminant > 0);
            Assert(IsTiny(a*x1*x1 + b*x1 + c));
            Assert(IsTiny(a*x2*x2 + b*x2 + c));
            break;
        }
        case RootsCount::Infinity:
        {
            Assert(IsTiny(a) && IsTiny(a) && IsTiny(c));
            break;
        }
    }

    if(IsTestFailed)
    {
        printf("%lgx^2 + %lgx + %lg = 0", a, b, c);
        printf("x1 = %lg", x1);
        printf("x2 = %lg", x2);
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

        printf("Test %i:\n", i);
        DisplayEquation(test.A, test.B, test.C);
        printf("[roots count] expected %i, given %i\n", test.RootsCount, rootsCount);
        
        if(test.RootsCount != rootsCount)
        {
            PrintTestResult(0);
            continue;
        }

        switch(test.RootsCount)
        {
            case RootsCount::One:
            {
                printf("[x1] expected %lg, given %lg\n", test.X1, x1);
                PrintTestResult(IsClose(test.X1, x1));
                break;
            }
            case RootsCount::Two:
            {
                printf("[x1 x2] expected %lg %lg, given %lg %lg\n", test.X1, test.X2, x1, x2);
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

int main()
{
    printf("Standart tests:\n");
    TestInfo tests[] = { 
        {0, 0, 1,    RootsCount::No, 0, 0}, 
        {0, 0, 0,    RootsCount::Infinity, 0, 0}, 
        {0, 5, 25,   RootsCount::One, -5, 0},
        {1, 0, -36,  RootsCount::Two, 60, -6}, 
        {3, 12, 0,   RootsCount::Two, 0, -4}, 
        {10, 6, 0.9, RootsCount::One, -0.3, 0}
    };
    SolveEquationTestArray(tests, 6);

    printf("Random tests:\n");
    srand(time(NULL));
    for(int i = 0; i < 15; i++)
        Run(SolveEquationRandomTest);
    
    getchar();
}