CFLAGS=-Wall -pedantic

default: example

example: example.c
	$(CC) $(CFLAGS) -Iinclude -o build/example example.c
	build/example
