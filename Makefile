CC = gcc
CFLAGS = -g -Wall
print:
	make -f Makefile.printHeader
copy:
	make -f Makefile.copy
multiply:
	make -f Makefile.multiply
.PHONY: clean
myWav:
	make -f Makefile.myWav
clean:
	rm -f *.o a.out printHeader copyWav multiplyWav myWav_test
.PHONY: all
all: clean print copy multiply
