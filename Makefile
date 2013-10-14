CFLAGS=-Wall -pedantic

default: example

test: example

example: example.c
	mkdir -p build
	$(CC) $(CFLAGS) -Iinclude -o build/example example.c
	build/example
