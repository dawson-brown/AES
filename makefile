CC=gcc
CFLAGS=-I. -lm
DEPS = parser.h aes.h file_handler/file_handler.h number_handler/number_handler.h
OBJ = main.o parser.o aes.o file_handler/file_handler.o number_handler/number_handler.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o aes $^ $(CFLAGS)