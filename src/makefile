all: build

build: proj.cpp equations.cpp IOLib.cpp equations.hpp IOLib.hpp my_assert.hpp
	g++ proj.cpp equations.cpp IOLib.cpp -o proj.exe -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE

test: equations.test.cpp equations.cpp IOLib.cpp TestLib.cpp equations.hpp IOLib.hpp TestLib.hpp
	g++ equations.test.cpp equations.cpp IOLib.cpp TestLib.cpp -o equations.test.exe