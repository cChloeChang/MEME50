CFLAGS = -g -Wall
CC = gcc
LIBS = -lm
INCLUDES = 
OBJS = a.o b.o c.o
SRCS = a.c b.c c.c prog1.c prog2.c
HDRS = abc.h
all: prog1 prog2

prog1: prog1.o ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ prog1.o ${OBJS} ${LIBS}
prog2: prog2.o ${OBJS}
	${CC} ${CFLAGS} -o $@ prog2.o ${OBJS} ${LIBS}
.c .o:
	${CC} ${CFLAGS} ${INCLUDES} -c $<

depend:
	makedepend ${SRCS}
clean:
	rm *.o core *~ # 清理.o 檔、core文件，通常是程式崩潰時生成的核心轉儲文件（core dump）、清理以~結尾的臨時文件

tar:
	tar cf code.tar Makefile *.c *.h testfile1
print:
	more Makefile ${HDRS} ${SRCS}|enscript -2r -p listing.ps
#DO NOT DELETE
