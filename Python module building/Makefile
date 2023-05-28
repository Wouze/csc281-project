CC = gcc
GFLAGS = -Wall -I\include

p: primemodule.o
	${CC} ${GFLAGS} -o p primemodule.o
	# del primemodule.o
	p
	
primemodule.o: primemodule.c
	${CC} ${GFLAGS} -c primemodule.c

