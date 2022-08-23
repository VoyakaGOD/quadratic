#include "equations.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int NumberOfTest = 1;
int IsTestFailed = 0;

/// Rejects the test.
void Assert(int condition)
{
    if(!condition)
        IsTestFailed = 1;
}

void AssertEqualDouble(double expected, double given, char* itemName)
{
    if(IsClose(expected, given))
        return;
    IsTestFailed = 1;
    printf("[%s] %lg expected, but %lg was given!", itemName, expected, given);
}

void AssertEqualRootsCount(RootsCount expected, RootsCount given, char* itemName)
{
    if(expected == given)
        return;
    IsTestFailed = 1;
    printf("[%s] %i expected, but %i was given!", itemName, expected, given);
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

void SolveEquationTest1()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(0, 0, 1, &x1, &x2);
    Assert(rootsCount == RootsCount::No);
}

void SolveEquationTest2()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(0, 0, 0, &x1, &x2);
    Assert(rootsCount == RootsCount::Infinity);
}

void SolveEquationTest3()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(0, 5, 25, &x1, &x2);
    Assert(rootsCount == RootsCount::One);
    Assert(IsClose(x1, -5));
}

void SolveEquationTest4()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(1, 0, -36, &x1, &x2);
    Assert(rootsCount == RootsCount::Two);
    Assert(isSetsEqual(x1, x2, -6, 6));
}

void SolveEquationTest5()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(3, 12, 0, &x1, &x2);
    Assert(rootsCount == RootsCount::Two);
    Assert(isSetsEqual(x1, x2, 0, -4));
}

void SolveEquationTest6()
{
    double x1 = 0, x2 = 0;
    RootsCount rootsCount = SolveEquation(10, 6, 0.9, &x1, &x2);
    Assert(rootsCount == RootsCount::One);
    Assert(IsClose(x1, -0.3));
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
    for(int i = 0; i < 100; i++)
        Run(SolveEquationRandomTest);
    
    getchar();
}