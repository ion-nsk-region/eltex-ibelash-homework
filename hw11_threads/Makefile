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

LIB = libmyshop.a
SRCS = $(filter-out ex_1.c, $(wildcard *.c))
OBJ := $(SRCS:.c=.o)

all: code_check ex_1.exe

ex_1.exe: ex_1.c $(LIB)
	@echo "\nСобираем главный исполняемый файл. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB) -lpthread

$(LIB): msg_lib $(LIB)($(OBJ))

msg_lib:
	@echo "\nСоздаём объектные файлы для статической библиотеки и собираем её."

code_check: $(SRCS) ex_1.c
	-cppcheck --enable=all --suppress=missingIncludeSystem $^
	#-clang-format -n --style=Google $^
	clang-format -i --style=Google $^

clean:
	rm -vf *.exe *.c~ *.a *.o

.PHONY: all clean code_check msg_lib
