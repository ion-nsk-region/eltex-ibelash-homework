CFLAGS = -g -Wall -Wextra -Werror
#CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror
LIB = libeltex_commander.a
SRC = $(filter-out eltex_commander.c, $(wildcard *.c))
OBJ := $(SRC:.c=.o)

eltex_commander.exe: eltex_commander.c $(LIB)
	@echo "\nСобираем главный исполняемый файл."
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB) -lncursesw

$(LIB): msg_lib $(LIB)($(OBJ))

msg_lib:
	@echo "\nСоздаём объектные файлы для статической библиотеки и собираем её."

.PHONY: clean msg_lib

clean:
	rm -vf *.o *.exe *.txt *.a
