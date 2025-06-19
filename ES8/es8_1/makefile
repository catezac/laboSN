CC = g++
CFLAGS = -Wall -O3 --std=c++17

esercizio8_1.exe : esercizio8_1.o ../../PRNG/random.o funzioni.o
	$(CC) ../../PRNG/random.o esercizio8_1.o funzioni.o -o main.exe

esercizio8_1.o : esercizio8_1.cpp ../funzioni.h
	$(CC) -c esercizio8_1.cpp -o esercizio8_1.o $(CFLAGS)

funzioni.o : ../funzioni.cpp ../funzioni.h
	$(CC) -c ../funzioni.cpp -o funzioni.o $(CFLAGS)

clean :
	rm -f *.o main.exe seed.out
	rm *.dat

run : main.exe
	./main.exe