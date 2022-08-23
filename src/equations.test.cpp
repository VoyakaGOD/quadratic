#include "equations.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int NumberOfTest = 1;
int IsTestFailed = 0;

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
    printf("test %i: %s!\n", NumberOfTest, IsTestFailed ? "fail" : "success");
    NumberOfTest++;
}

/// Compare A{a1, a2} and B{b1, b2} without order.
int isSetsEqual(double a1, double a2, double b1, double b2)
{
    return (IsTiny(a1 - b1) && IsTiny(a2 - b2)) || (IsTiny(a1 - b2) && IsTiny(a2 - b1));
}

/// Is difference between a and b is tiny.
int IsClose(double a, double b)
{
    return IsTiny(a - b);
}

int AssertEqualX(double given, double expected)
{
    if(Assert(IsClose(expected, given)))
        printf("[x] %lg expected, but %lg was given!\n", expected, given);
}

int AssertEqualRootsCount(RootsCount given, RootsCount expected)
{
    if(Assert(expected == given))
        printf("[roots count] %i expected, but were %i!\n", expected, given);
}

int AssertEqualXs(double given1, double given2, double expected1, double expected2)
{
    if(Assert((IsTiny(given1 - expected1) && IsTiny(given2 - expected2)) || (IsTiny(given1 - expected2) && IsTiny(given2 - expected1))))
        printf("[{x1, x2}] {%lg, %lg} expected, but {%lg, %lg} was given!\n", expected1, expected2, given1, given2);
}

void SolveEquationTest1()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(0, 0, 1, &x1, &x2);
    AssertEqualRootsCount(rootsCount, RootsCount::No);
}

void SolveEquationTest2()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(0, 0, 0, &x1, &x2);
    AssertEqualRootsCount(rootsCount, RootsCount::Infinity);
}

void SolveEquationTest3()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(0, 5, 25, &x1, &x2);
    AssertEqualRootsCount(rootsCount, RootsCount::One);
    AssertEqualX(x1, -5);
}

void SolveEquationTest4()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(1, 0, -36, &x1, &x2);
    AssertEqualRootsCount(rootsCount, RootsCount::Two);
    AssertEqualXs(x1, x2, -6, 6);
}

void SolveEquationTest5()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(3, 12, 0, &x1, &x2);
    AssertEqualRootsCount(rootsCount, RootsCount::Two);
    AssertEqualXs(x1, x2, 0, -24);
}

void SolveEquationTest6()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(10, 6, 0.9, &x1, &x2);
    AssertEqualRootsCount(rootsCount, RootsCount::One);
    AssertEqualX(x1, -0.23);
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

int main()
{
    Run(SolveEquationTest1);
    Run(SolveEquationTest2);
    Run(SolveEquationTest3);
    Run(SolveEquationTest4);
    Run(SolveEquationTest5);
    Run(SolveEquationTest6);

    srand(time(NULL));
    for(int i = 0; i < 15; i++)
        Run(SolveEquationRandomTest);
    
    getchar();
}