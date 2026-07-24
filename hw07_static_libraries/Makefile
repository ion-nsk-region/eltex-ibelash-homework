CC = gcc
FLAGS = -Wall -Werror -Wextra
ARCHIVER = ar
ARCHIVER_OPTS = rc

LIB = calc
HEADERS = calc.h
SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)

main.exe: main.c lib$(LIB).a
	$(CC) $(FLAGS) -o $@ $< -L. -l$(LIB)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

lib$(LIB).a: $(OBJ)
	$(ARCHIVER) $(ARCHIVER_OPTS) lib$(LIB).a $(OBJ)

.PHONY: clean

clean:
	rm -f *.o *.c~ *.h~ main.exe lib$(LIB).a
