CFLAGS = -Wall -Wextra -Werror
LIB = libex_1.a
SRC = $(wildcard *File.c)
OBJ := $(SRC:.c=.o)

ex_1.exe: ex_1.c $(LIB)
	@echo "\nСобираем главный исполняемый файл."
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB)

$(LIB): msg_lib $(LIB)($(OBJ))

msg_lib:
	@echo "\nСоздаём объектные файлы для статической библиотеки и собираем её."

.PHONY: clean msg_lib

clean:
	rm -vf *.o *.exe *.txt *.a

