CC=gcc
CFLAGS=-lm
RM=rm -f

default: clean quadtree

quadtree: quadtree.c
	$(CC) -o quadtree quadtree.c $(CFLAGS)

clean:
	rm -f quadtree
