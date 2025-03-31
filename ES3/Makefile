CC = g++
CFLAGS = -Wall -O3 --std=c++17

esercizio3_1.exe : esercizio3_1.o ../PRNG/random.o funzioni.o
	$(CC) ../PRNG/random.o funzioni.o esercizio3_1.o -o main.exe

esercizio3_1.o : esercizio3_1.cpp funzioni.h
	$(CC) -c esercizio3_1.cpp -o esercizio3_1.o $(CFLAGS)

funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)
	
clean :
	rm -f *.o main.exe seed.outR

run : main.exe
	./main.exe