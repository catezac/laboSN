CC = g++
CFLAGS = -Wall -O3 --std=c++17


esercizio1_2.exe : esercizio1_2.o ../funzioni.o ../../PRNG/random.o
	$(CC) ../../PRNG/random.o ../funzioni.o esercizio1_2.o -o main.exe

esercizio1_2.o : esercizio1_2.cpp ../../PRNG/random.h ../funzioni.h
	$(CC) -c esercizio1_2.cpp  -o esercizio1_2.o $(CFLAGS)

random.o : ../../PRNG/random.cpp ../../PRNG/random.h
	$(CC) -c ../../PRNG/random.cpp -o ../../PRNG/random.o $(CFLAGS)

funzioni.o : ../funzioni.cpp ../funzioni.h
	$(CC) -c ../funzioni.cpp -o funzioni.o $(CFLAGS)

clean :
	rm *.o main_3.exe seed.out