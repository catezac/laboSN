CXX = mpicxx
CXXFLAGS = -O3 --std=c++14
LDFLAGS = -larmadillo

SRC = main.cpp funzioni.cpp city.cpp chromosome.cpp population.cpp
OBJ = $(SRC:.cpp=.o) ../../PRNG/random.o
EXE = main.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXE)

run: mpiexec -np 2 main.exe

.PHONY: all clean