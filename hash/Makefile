include ../Makefile.inc
OBJS:=$(patsubst %.c,%.o,$(wildcard *.c))


.PHONY:all clean

all:${OBJS}

%.o:%.c
	${CC} -c ${CFLAGS} $< -o $@
clean:
	@echo "Remove all obj files"
	rm ./*.o

