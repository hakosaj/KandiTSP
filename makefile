LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: simulation

Constants.o: Constants.cpp
		g++ -c -fopenmp "Constants.cpp" -o Constants.o

Objects.o: Objects.cpp
		g++ -c -fopenmp "Objects.cpp" -o Objects.o

AlgFunctions.o: AlgFunctions.cpp	
		g++ -c -fopenmp "AlgFunctions.cpp" -o AlgFunctions.o

Functions.o: Functions.cpp
		g++ -c -fopenmp "Functions.cpp" -o Functions.o

InitializeFunctions.o: InitializeFunctions.cpp
		g++ -c -fopenmp "InitializeFunctions.cpp" -o InitializeFunctions.o

main.o: main.cpp
		g++ -c -fopenmp "main.cpp" -o main.o

simulation: Constants.o Objects.o AlgFunctions.o Functions.o InitializeFunctions.o main.o
		@echo "** Building the simulation"
		g++ -o simulation -fopenmp  AlgFunctions.o Constants.o Functions.o InitializeFunctions.o main.o Objects.o $(LIBS)

clean:
		@echo "** Removing object files and executable..."
		rm -f thegame *.o

install:
		@echo '** Installing...'
		cp thegame /usr/bin

uninstall:
		@echo '** Uninstalling...'
		rm -f /usr/bin/thegame