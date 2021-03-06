CC=gcc
CFLAGS=-lm -Wall
PFLAGS=-fopenmp

serial: main.c integrate_serial.o timer.o
	$(CC) main.c integrate_serial.o timer.o $(CFLAGS)
	
timer.o: timer.c
	$(CC) -c timer.c

integrate_serial.o: integrate.c
	$(CC) -c integrate.c -o integrate_serial.o

parallel: main.c integrate_parallel.o timer.o
	$(CC) main.c integrate_parallel.o timer.o  $(CFLAGS) $(PFLAGS) -o omp.out
	
integrate_parallel.o: integrate.c
	$(CC) -c integrate.c -o integrate_parallel.o $(PFLAGS)
