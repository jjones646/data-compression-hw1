DIR=
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=

_DEPS = morse.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = morse.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

morse: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
