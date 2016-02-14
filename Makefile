CC=gcc
CFLAGS=-I.
DEPS = morse
OBJ = morse.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

morse: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
