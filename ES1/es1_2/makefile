CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio1_2.o : esercizio1_2.cpp
	$(CC) -c esercizio1_2.cpp -o esercizio1_2.o $(CFLAGS)
esercizio1_2.exe : esercizio1_2.o ../../PRNG/random.o
	$(CC) ../../PRNG/random.o esercizio1_2.o -o main_2.exe