
CC=gcc
CFLAGS=-I. -lm
DEPS = modes.h aes.h minunit.h
OBJ = test.o modes.o aes.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o test $^ $(CFLAGS)