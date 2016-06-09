include Makefile.inc
OBJS:=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
SUBS = leetcode binarysearch bitwise cplusplus dynamicprogramming hash list matrix numbers sequenceandstring sorting stackandqueue tree greedy

.PHONY:all $(SUBS) clean #subdir

all:${OBJS} $(SUBS) #subdirs

$(SUBS):
	${MAKE} -C $@
#subdirs:
#	for dir in ${SUBS}; do \
#            ${MAKE} -C $$dir; \
#    	done

%.o:%.cpp
	${CXX} -c ${CPPFLAGS} $< -o $@
clean:
	@echo "Remove all obj files"
	rm ./*.o
	for dir in ${SUBS}; do \
	    rm $$dir/*.o; \
	done

