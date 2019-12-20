CC=gcc
CFLAGS=-I. -lm
DEPS = aes.h
OBJ = main.o aes.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o aes $^ $(CFLAGS)