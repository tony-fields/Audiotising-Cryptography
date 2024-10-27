CC = gcc

# Compilation options:
# -g: include debugging info symbols
# -Wall: enable all warnings
CFLAGS = -g -Wall

print:
	make -f Makefile.printHeader

copy:
	make -f Makefile.copy


.PHONY: clean
clean:
	rm -f *.o a.out printHeader copyWav

.PHONY: all
all: clean myprogram
