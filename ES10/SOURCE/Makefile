CC = g++
CFLAGS = -O3 --std=c++14
AFLAGS = -larmadillo
all: main.exe
main.exe :  main.o population.o chromosome.o city.o ../../PRNG/random.o funzioni.o
	$(CC) population.o chromosome.o ../../PRNG/random.o main.o city.o funzioni.o -o main.exe $(AFLAGS)
main.o : main.cpp population.h chromosome.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
population.o : population.cpp population.h chromosome.h city.h funzioni.h
	$(CC) -c population.cpp -o population.o $(CFLAGS)
chromosome.o : chromosome.cpp chromosome.h city.h funzioni.h
	$(CC) -c chromosome.cpp -o chromosome.o $(CFLAGS)
city.o : city.cpp city.h
	$(CC) -c city.cpp -o city.o $(CFLAGS)
funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)

clean :
	rm *.o main.exe
remove:
	rm ../OUTPUT/*.*
	rm ../OUTPUT/CONFIG/*.*