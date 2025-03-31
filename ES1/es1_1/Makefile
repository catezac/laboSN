CC = g++
CFLAGS = -Wall -O3 --std=c++17


esercizio1_1.o : esercizio1_1.cpp
	$(CC) -c esercizio1_1.cpp -o esercizio1_1.o $(CFLAGS)

esercizio1_1.exe : esercizio1_1.o ../../PRNG/random.o
	$(CC) ../../PRNG/random.o esercizio1_1.o -o main.exe