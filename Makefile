CC = gcc
CFLAGS = -g -Wall
print:
	make -f Makefile.printHeader
copy:
	make -f Makefile.copy
multiply:
	make -f Makefile.multiply
.PHONY: clean
clean:
	rm -f *.o a.out printHeader copyWav multiplyWav
.PHONY: all
all: clean print copy multiply
