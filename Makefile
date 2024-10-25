CC = gcc

# Compilation options:
# -g: include debugging info symbols
# -Wall: enable all warnings
CFLAGS = -g -Wall

print:
	make -f Makefile.printHeader



.PHONY: clean
clean:
	rm -f *.o a.out printHeader

.PHONY: all
all: clean myprogram
