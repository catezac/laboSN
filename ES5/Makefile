CC = g++
CFLAGS = -Wall -O3 --std=c++17

esercizio5.exe : esercizio5.o ../PRNG/random.o Posizione.o funzioni.o
	$(CC) ../PRNG/random.o esercizio5.o Posizione.o funzioni.o -o main.exe

esercizio5.o : esercizio5.cpp funzioni.h
	$(CC) -c esercizio5.cpp -o esercizio5.o $(CFLAGS)

Posizione.o : Posizione.cpp Posizione.h
	$(CC) -c Posizione.cpp -o Posizione.o $(CFLAGS)

funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)

	
clean :
	rm -f *.o main.exe seed.out

run : main.exe
	./main.exe