CC= gcc
CFLAGS= -O1

p: 
	@${CC} $(CFLAGS) -o p project.c
	p

