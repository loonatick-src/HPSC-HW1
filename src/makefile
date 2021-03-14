CC=gcc
CFLAGS=-lm -Wall
PFLAGS=-fopenmp
TARGET=../bin

testing=$(TARGET)/testing.o
integrate_parallel=$(TARGET)/integrate_parallel.o
integrate_seial=$(TARGET)/integrate_serial.o
timer=$(TARGET)/timer.o


serial: main.c $(integrate_serial) $(timer) $(testing)
	$(CC) main.c ../bin/integrate_serial.o ../bin/timer.o ../bin/testing.o $(CFLAGS) -o ../bin/a.out

$(testing): testing.c
	$(CC) -c testing.c -o ../bin/testing.o

$(timer): timer.c
	$(CC) -c timer.c -o ../bin/timer.o

$(integrate_serial): integrate.c
	$(CC) -c integrate.c -o $(integrate_serial)

parallel: main.c $(TARGET)/integrate_parallel.o $(TARGET)/testing.o $(TARGET)/timer.o
	$(CC) main.c ../bin/testing.o ../bin/integrate_parallel.o ../bin/timer.o $(PFLAGS) $(CFLAGS) -o ../bin/omp.out
	
$(integrate_parallel): integrate.c
	$(CC) -c integrate.c -o ../bin/integrate_parallel.o $(PFLAGS)

convergence: serial
	./convergence.sh
    
clean:
	rm ../bin/*.out
	rm ../*.aux
	rm ../*.fdb_latexmk
	rm -rf ../*minted-main
	rm ../*.log
	rm ../*.fls
	rm ../*.synctex.gz
