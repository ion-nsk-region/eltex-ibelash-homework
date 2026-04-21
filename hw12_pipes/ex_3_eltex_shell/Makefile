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

MAIN = ex_3
LIB = lib_eltex_shell.a
SRCS = $(filter-out $(MAIN).c, $(wildcard *.c))
OBJ := $(SRCS:.c=.o)

all: code_check $(MAIN).exe

$(MAIN).exe: $(MAIN).c $(LIB)
	@echo "\nСобираем главный исполняемый файл. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB)

$(LIB): msg_lib $(LIB)($(OBJ))

msg_lib:
	@echo "\nСоздаём объектные файлы для статической библиотеки и собираем её."

code_check: $(SRCS) $(MAIN).c
	-cppcheck --enable=all --suppress=missingIncludeSystem $^
	#-clang-format -n --style=Google $^
	clang-format -i --style=Google $^

clean:
	rm -vf *.exe *.c~ *.h~ *.a *.o Makefile~

.PHONY: all clean code_check msg_lib
