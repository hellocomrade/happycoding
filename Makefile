include Makefile.inc
OBJS:=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
SUBS = binarysearch bitwise cplusplus dynamicprogramming hash list matrix numbers sequenceandstring sorting stackandqueue tree

.PHONY:all subdir clean

all:${OBJS} subdirs

subdirs:
	for dir in ${SUBS}; do \
            ${MAKE} -C $$dir; \
    	done

%.o:%.cpp
	${CXX} -c ${CPPFLAGS} $< -o $@
clean:
	@echo "Remove all obj files"
	rm ./*.o
	for dir in ${SUBS}; do \
	    rm $$dir/*.o; \
	done

