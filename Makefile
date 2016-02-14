CC=g++
CFLAGS=-std=c++14 -lstdc++
DEPS = morse.hpp
OBJS = morse.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

morse: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f morse $(OBJS)
