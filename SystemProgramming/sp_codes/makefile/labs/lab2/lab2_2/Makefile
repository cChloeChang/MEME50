CC = gcc
CFLAGS = -I.

hellomake: hellomake.o hellofunc.o
	$(CC) -o hellomake hellomake.o hellofunc.o
hellomake.o: hellomake.c hellomake.h
	$(CC) -c hellomake.c $(CFLAGS)
hellofunc.o: hellofunc.c hellomake.h
	$(CC) -c hellofunc.c $(CFLAGS)
