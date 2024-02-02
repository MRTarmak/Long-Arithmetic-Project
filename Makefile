biglib: bfnumlib.cpp bfnumlib.hpp
	g++ -c bfnumlib.cpp -o biglib.o 

main: main.cpp biglib.o
	g++ main.cpp biglib.o