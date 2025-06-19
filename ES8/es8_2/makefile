CC = g++
CFLAGS = -Wall -O3 --std=c++17

esercizio8_2.exe : esercizio8_2.o ../../PRNG/random.o funzioni.o
	$(CC) ../../PRNG/random.o esercizio8_2.o funzioni.o -o main.exe

esercizio8_2.o : esercizio8_2.cpp ../funzioni.h
	$(CC) -c esercizio8_2.cpp -o esercizio8_2.o $(CFLAGS)

funzioni.o : ../funzioni.cpp ../funzioni.h
	$(CC) -c ../funzioni.cpp -o funzioni.o $(CFLAGS)

clean :
	rm -f *.o main.exe seed.out "H_T.dat"

run : main.exe
	./main.exe