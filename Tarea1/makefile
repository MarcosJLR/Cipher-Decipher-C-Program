CC=gcc
CFLAGS=-I.
DEPS = cipher.h  date.h  linkedlist.h  main.h
OBJ = cipher.o  date.o  linkedlist.o  main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

decipher: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm decipher
	@rm $(OBJ)