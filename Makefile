CC= gcc
CFLAGS= -Wall

p: 
	@${CC} $(CFLAGS) -o p project.c
	p

