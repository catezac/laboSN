CC = g++
CFLAGS = -Wall -O3 --std=c++17

esercizio2_1.exe : esercizio2_1.o ../../PRNG/random.o funzioni.o
	$(CC) ../../PRNG/random.o esercizio2_1.o funzioni.o -o main.exe

esercizio2_1.o : esercizio2_1.cpp ../funzioni.h
	$(CC) -c esercizio2_1.cpp -o esercizio2_1.o $(CFLAGS)

funzioni.o : ../funzioni.cpp ../funzioni.h
	$(CC) -c ../funzioni.cpp -o funzioni.o $(CFLAGS)

clean :
	rm -f *.o main.exe seed.outR

run : main.exe
	./main.exe