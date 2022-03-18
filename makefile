CC=gcc
CFLAGS=-I. -pthread
DEPS = prod_cons_MT.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

project2: main.o prod_cons_MT.o
	$(CC) -o $@ $^ $(CFLAGS)
