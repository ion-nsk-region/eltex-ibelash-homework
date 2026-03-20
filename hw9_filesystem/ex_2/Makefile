ifndef BUILD_MODE
    BUILD_MODE = Release
endif

ifeq ($(BUILD_MODE), Release)
	CFLAGS = -Wall -Wextra -Werror
else ifeq ($(BUILD_MODE), Debug)
	CFLAGS = -g -Wall -Wextra -Werror
else ifeq ($(BUILD_MODE), Asan)
	CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror
endif

LIB = libeltex_commander.a
SRC = $(filter-out eltex_commander.c, $(wildcard *.c))
OBJ := $(SRC:.c=.o)

eltex_commander.exe: eltex_commander.c $(LIB)
	@echo "\nСобираем главный исполняемый файл. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB) -lncursesw

$(LIB): msg_lib $(LIB)($(OBJ))

msg_lib:
	@echo "\nСоздаём объектные файлы для статической библиотеки и собираем её."

.PHONY: clean msg_lib

clean:
	rm -vf *.o *.exe *.txt *.a
