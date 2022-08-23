@echo off
g++ proj.cpp equations.hpp equations.cpp IOLib.hpp IOLib.cpp -o proj.exe || pause
proj.exe || pause