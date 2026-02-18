CFLAGS = -Wall -Wextra -Werror
LIB = libex_1.a
SRC = $(wildcard *File.c)
OBJ := $(SRC:.c=.o)

ex_1.exe: ex_1.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB)

$(LIB): $(LIB)($(OBJ)) 

.PHONY: clean

clean:
	rm -f *.o *.exe *.txt *.a

