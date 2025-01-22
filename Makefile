principal: regra1 regra2
	g++ main.o MatrizEsparsas.o -o main 
regra1: main.cpp
	g++ -c main.cpp 
regra2: MatrizEsparsas.cpp
	g++ -c MatrizEsparsas.cpp