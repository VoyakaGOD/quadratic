#ifndef MY_ASSERT_HEADER
#define MY_ASSERT_HEADER

#include <iostream>

#define assert(condition) if (!(condition))\
printf("Assertion failed: %s, file %s, func %s, line %d\n", #condition, __FILE__, __PRETTY_FUNCTION__, __LINE__);

#endif