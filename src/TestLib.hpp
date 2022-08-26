#ifndef TEST_LIB
#define TEST_LIB

#include <stdio.h>

#define PRINT(...) printf(__VA_ARGS__); PrintLog(__VA_ARGS__)

/// Colored print of fail or success.
void PrintTestResult(int success);

/// Open or create new log file.
void OpenLogFile(const char *path);

/// Write data to opened log file.
void PrintLog(const char *format, ...);

/// Close log file.
void CloseLogFile();

#endif