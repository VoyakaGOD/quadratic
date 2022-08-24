@echo off
g++ equations.test.cpp equations.cpp IOLib.cpp -o equations.test.exe || pause
equations.test.exe || pause