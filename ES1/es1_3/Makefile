CC = g++
CFLAGS = -Wall -O3 --std=c++11


esercizio1_3.exe : esercizio1_3.o random.o ../funzioni.o
	$(CC) ../../PRNG/random.o esercizio1_3.o ../funzioni.o -o main_3.exe

esercizio1_3.o : esercizio1_3.cpp ../funzioni.h ../../PRNG/random.h
	$(CC) -c esercizio1_3.cpp -o esercizio1_3.o $(CFLAGS)

random.o : ../../PRNG/random.cpp ../../PRNG/random.h
	$(CC) -c ../../PRNG/random.cpp -o ../../PRNG/random.o $(CFLAGS)

funzioni.o : ../funzioni.cpp ../funzioni.h
	$(CC) -c ../funzioni.cpp -o funzioni.o $(CFLAGS)

clean :
	rm *.o main_3.exe seed.out