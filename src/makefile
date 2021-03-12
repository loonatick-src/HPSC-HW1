CC=gcc
CFLAGS=-lm -Wall
PFLAGS=-fopenmp

serial: main.c integrate_serial timer testing
	$(CC) main.c ../bin/integrate_serial.o ../bin/timer.o ../bin/testing.o $(CFLAGS) -o ../bin/a.out

testing: testing.c
	$(CC) -c testing.c -o ../bin/testing.o

timer: timer.c
	$(CC) -c timer.c -o ../bin/timer.o

integrate_serial: integrate.c
	$(CC) -c integrate.c -o ../bin/integrate_serial.o 

parallel: main.c integrate_parallel timer testing
	$(CC) main.c bin/integrate_parallel.o bin/timer.o bin/testing.o $(CFLAGS) $(PFLAGS) -o ../bin/omp.out
	
integrate_parallel: integrate.c
	$(CC) -c integrate.c -o ../bin/integrate_parallel.o $(PFLAGS)

convergence: serial
	./convergence.sh
    
clean:
	rm ../bin/*.out
