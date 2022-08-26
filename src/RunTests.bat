@echo off
g++ equations.test.cpp equations.cpp IOLib.cpp TestLib.cpp -o equations.test.exe || pause
equations.test.exe log.txt || pause