#include "TestInfo.hpp"
#include "TestLib.hpp"
#include "IOLib.hpp"
#include <time.h>

#define TEST_ASSERT(condition) if(!(condition)) *__success = 0;

const int RandomTestCount = 15;

/// Compare roots taken in account NAN values.
int CompareRoots(double expected, double given)
{
    if (isnan(expected) && isnan(given))
        return 1;
    if (isnan(expected) && !isnan(given))
        return 0;
    if (!isnan(expected) && isnan(given))
        return 0;
    return IsTiny(expected - given);
}

/// @param[in] e1 first expected root
/// @param[in] e2 second expected root
/// @param[in] g1 first given root
/// @param[in] g2 second given root
int IsRootsEqual(double e1, double e2, double g1, double g2)
{
    return (CompareRoots(e1, g1) && CompareRoots(e2, g2)) || (CompareRoots(e1, g2) && CompareRoots(e2, g1));
}

/// Is difference between a and b is less than 1e-7.
int IsClose(double a, double b)
{
    return IsTiny(a - b);
}

/// Test SolveEquation function with random parameters.
/// @param[out] __success result of the test
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
        case NO_ROOTS:
        {
            TEST_ASSERT(discriminant < 0);
            break;
        }
        case ONE_ROOT:
        {    
            TEST_ASSERT(IsTiny(discriminant));
            TEST_ASSERT(IsTiny(a*x1*x1 + b*x1 + c));
            break;
        }
        case TWO_ROOTS:
        {
            TEST_ASSERT(discriminant > 0);
            TEST_ASSERT(IsTiny(a*x1*x1 + b*x1 + c));
            TEST_ASSERT(IsTiny(a*x2*x2 + b*x2 + c));
            break;
        }
        case INF_ROOTS:
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

/// @brief Test SolveEquation function with parameters specified by TestInfo for each element of tests array.
/// @param[in] tests array of tests
/// @param[in] count the number of test
/// @return the number of successfuly passed tests
int SolveEquationTestArray(TestInfo *tests, int count)
{
    int successfulyTestsCount = 0;
    for(int i = 0; i < count; i++)
    {
        TestInfo test = tests[i];
        double x1 = NAN, x2 = NAN;
        RootsCount rootsCount = SolveEquation(test.A, test.B, test.C, &x1, &x2);

        PRINT("Test %i:\n", i);
        
        if(test.RootsCount == rootsCount && IsRootsEqual(test.X1, test.X2, x1, x2))
        {
            PrintTestResult(1);
            successfulyTestsCount++;
            continue;
        }

        DisplayEquation(test.A, test.B, test.C);
        PRINT("[roots count] expected %i, given %i\n", test.RootsCount, rootsCount);
        switch(test.RootsCount)
        {
            case ONE_ROOT:
            {
                PRINT("[x1] expected %lg, given %lg\n", test.X1, x1);
                break;
            }
            case TWO_ROOTS:
            {
                PRINT("[x1 x2] expected %lg %lg, given %lg %lg\n", test.X1, test.X2, x1, x2);
                break;
            }
        }
        PrintTestResult(0);
    }
    return successfulyTestsCount;
}

int main(int argc, char* argv[])
{
    if (argc == 2)
        OpenLogFile(argv[1]);

    PRINT("Standart tests:\n");
    int standartTestsCount = 6;
    TestInfo tests[] = { 
        {0,  0,  1,    NO_ROOTS,    NAN,    NAN}, 
        {0,  0,  0,    INF_ROOTS,   NAN,    NAN}, 
        {0,  5,  25,   ONE_ROOT,    -5,   NAN},
        {1,  0,  -36,  TWO_ROOTS,   6,    -6}, 
        {3,  12, 0,    TWO_ROOTS,   0,    -4}, 
        {10, 6,  0.9,  ONE_ROOT,    -0.3, NAN}
    };
    
    int successfulyTestsCount = SolveEquationTestArray(tests, standartTestsCount);

    PRINT("Random tests:\n");
    srand(time(NULL));
    for(int i = 0; i < RandomTestCount; i++)
    {
        int success = 1;
        PRINT("test %d: start!\n", i);
        SolveEquationRandomTest(&success);
        PrintTestResult(success);
        successfulyTestsCount += success;
    }

    PRINT("<--------Passed: %d/%d!-------->\n", successfulyTestsCount, (standartTestsCount + RandomTestCount));

    CloseLogFile();
    
    getchar();
}