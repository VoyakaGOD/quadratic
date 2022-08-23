@echo off
g++ equations.test.cpp equations.hpp equations.cpp -o equations.test.exe || pause
equations.test.exe || pause