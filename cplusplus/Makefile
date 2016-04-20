include ../Makefile.inc
OBJS:=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

.PHONY:all clean

all:${OBJS}

%.o:%.cpp
	${CXX} -c ${CPPFLAGS} $< -o $@
clean:
	@echo "Remove all obj files"
	rm ./*.o

