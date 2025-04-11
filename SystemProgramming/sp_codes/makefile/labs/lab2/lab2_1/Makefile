hellomake: hellomake.o hellofunc.o
	gcc -o hellomake hellomake.o hellofunc.o
hellomake.o: hellomake.c hellomake.h
	gcc -c hellomake.c -I.
hellofunc.o: hellofunc.c hellomake.h
	gcc -c hellofunc.c -I.
