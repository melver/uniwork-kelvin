
CC=gcc -g -Wall -D_M8C
NAME=test
OBJECTS=../core/xlowpan.o ../core/hashmap.o ../core/dynmem.o

.PHONY: all
all: $(NAME)

test: $(NAME).o $(OBJECTS)
	$(CC) -o $@ $< $(OBJECTS)

%.o: %.c
	$(CC) -o $@ -c $<

.PHONY: clean
clean:
	- rm -v *.o
	- rm -v $(OBJECTS)
	- rm -v $(NAME)

