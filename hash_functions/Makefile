CC=gcc
CFLAGS=-I. -lm
DEPS = sha.h test.h
OBJ = test.o sha.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o test $^ $(CFLAGS)