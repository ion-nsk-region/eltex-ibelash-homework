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

MAIN_SERVER = posix_server
MAIN_CLIENT = posix_client
LIB = libmq_chat.a
SRCS = $(filter-out $(MAIN_SERVER).c $(MAIN_CLIENT).c, $(wildcard *.c))
OBJ := $(SRCS:.c=.o)

all: code_check $(MAIN_SERVER).exe $(MAIN_CLIENT).exe

server: $(MAIN_SERVER).exe

client: $(MAIN_CLIENT).exe

$(MAIN_SERVER).exe: $(MAIN_SERVER).c $(LIB)
	@echo "\nСобираем исполняемый файл сервера. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB)

$(MAIN_CLIENT).exe: $(MAIN_CLIENT).c $(LIB)
	@echo "\nСобираем исполняемый файл клиента. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(LIB)

$(LIB): msg_lib $(LIB)($(OBJ))

msg_lib:
	@echo "\nСоздаём объектные файлы для статической библиотеки и собираем её."

code_check: $(SRCS) $(MAIN_SERVER).c $(MAIN_CLIENT).c
	-cppcheck --enable=all --suppress=missingIncludeSystem $^
	#-clang-format -n --style=Google $^
	clang-format -i --style=Google $^

clean:
	rm -vf *.exe *.c~ *.a *.o

.PHONY: all clean code_check msg_lib server client

