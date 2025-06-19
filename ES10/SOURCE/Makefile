CXX = mpicxx
CXXFLAGS = -O3 --std=c++14
LDFLAGS = -larmadillo

SRC = parallel.cpp funzioni.cpp city.cpp chromosome.cpp population.cpp
OBJ = $(SRC:.cpp=.o) ../../PRNG/random.o
EXE = simulator.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXE)

.PHONY: all clean