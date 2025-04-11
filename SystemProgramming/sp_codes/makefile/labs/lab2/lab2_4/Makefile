CC = gcc
CFLAGS = -I.
DEPS = hellomake.h
OBJ = hellomake.o hellofunc.o
all: hellomake

hellomake: $(OBJ)
	$(CC) -o $@ $(OBJ)
$(OBJ): %.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o hellomake
