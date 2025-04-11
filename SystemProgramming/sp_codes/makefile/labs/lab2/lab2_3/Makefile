CC = gcc
CFLAGS = -I.
DEPS = hellomake.h

hellomake: hellomake.o hellofunc.o
	$(CC) -o $@ hellomake.o hellofunc.o
%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o hellomake
