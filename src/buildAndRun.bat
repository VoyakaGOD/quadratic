@echo off
g++ proj.cpp equations.cpp IOLib.cpp -o proj.exe || pause
proj.exe || pause