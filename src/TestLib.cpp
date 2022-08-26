#include "TestLib.hpp"
#include <windows.h>
#include <stdarg.h>

static FILE *LogFile = NULL;

void PrintTestResult(int success)
{
    PRINT("Result: ");

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cInfo = {};
    GetConsoleScreenBufferInfo (hOut, &cInfo);
    WORD oldColor = cInfo.wAttributes;

    SetConsoleTextAttribute(hOut, success ? FOREGROUND_GREEN : FOREGROUND_RED);
    PRINT("%s!\n", success ?  "success" : "fail");

    SetConsoleTextAttribute(hOut, oldColor);
}

void OpenLogFile(const char *path)
{
    LogFile = fopen(path, "w");
}

void PrintLog(const char *format, ...)
{
    if(LogFile == NULL)
        return;
    
    va_list args;
    va_start(args, format);
    vfprintf(LogFile, format, args);
    va_end(args);
}

void CloseLogFile()
{
    if(LogFile != NULL)
    {
        fclose(LogFile);
    }
}