#include "equations.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int NumberOfTest = 1;
int IsTestFailed = 0;

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
/// @return 1 if condtion failed else 0
int Assert(int condition)
{
    if(condition)
        return 0;
    IsTestFailed = 1;
    return 1;
}

/// Run the test and show result.
void Run(void (*test)())
{
    IsTestFailed = 0;
    printf("test %i: start!\n", NumberOfTest);
    test();
    printf("---------------------------------------Result: %s!\n", IsTestFailed ? "fail[X]" : "success[V]");
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

void SolveEquationRandomTest()
{
    double a = rand() % 2001 - 1000;
    double b = rand() % 2001 - 1000;
    double c = rand() % 2001 - 1000;

    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(a, b, c, &x1, &x2);

    double D = b*b - 4*a*c;
    switch(rootsCount)
    {
        case RootsCount::No:
            Assert(D < 0);
            break;
        case RootsCount::One:
            Assert(IsTiny(D));
            Assert(IsTiny(a*x1*x1 + b*x1 + c));
            break;
        case RootsCount::Two:
            Assert(D > 0);
            Assert(IsTiny(a*x1*x1 + b*x1 + c));
            Assert(IsTiny(a*x2*x2 + b*x2 + c));
            break;
        case RootsCount::Infinity:
            Assert(IsTiny(a) && IsTiny(a) && IsTiny(c));
            break;
    }

    if(IsTestFailed)
    {
        printf("%lgx^2 + %lgx + %lg = 0", a, b, c);
        printf("x1 = %lg", x1);
        printf("x2 = %lg", x2);
    }
}

void SolveEquationTestArray(TestInfo *tests, int count)
{
    for(int i = 0; i < count; i++)
    {
        TestInfo test = tests[i];
        double x1 = 0, x2 = 0;
        RootsCount rootsCount = SolveEquation(test.A, test.B, test.C, &x1, &x2);
        printf("Test %i:\n", i);
        if(!IsTiny(test.A))
            printf("%lgx^2 + ", test.A);
        if(!IsTiny(test.B))
            printf("%lgx + ", test.B);
        printf("%lg = 0\n", test.C);
        printf("[roots count] expected %i, given %i\n", test.RootsCount, rootsCount);
        if(test.RootsCount != rootsCount)
        {
            printf("---------------------------------------Result: fail[X]!\n");
            continue;
        }
        switch(test.RootsCount)
        {
            case RootsCount::One:
                printf("[x1] expected %lg, given %lg\n", test.X1, x1);
                printf("---------------------------------------Result: %s!\n", IsClose(test.X1, x1) ? "success[V]" : "fail[X]");
                break;
            case RootsCount::Two:
                printf("[x1] expected %lg, given %lg\n", test.X1, x1);
                printf("[x2] expected %lg, given %lg\n", test.X2, x2);
                printf("---------------------------------------Result: %s!\n", IsSetsEqual(test.X1, test.X2, x1, x2) ? "success[V]" : "fail[X]");
                break;
            default:
                printf("---------------------------------------Result: success[V]!\n");
                break;
        }
    }
}

int main()
{
    printf("Standart tests:\n");
    TestInfo tests[] = { 
    {0, 0, 1,    RootsCount::No, 0, 0}, 
    {0, 0, 0,    RootsCount::Infinity, 0, 0}, 
    {0, 5, 25,   RootsCount::One, -15, 0},
    {1, 0, -36,  RootsCount::Two, 6, -6}, 
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