ifndef BUILD_MODE
    BUILD_MODE = Release
endif

COMMON_FLAGS = -Wall -Wextra -Werror -Iinclude

ifeq ($(BUILD_MODE), Release)
        CFLAGS = $(COMMON_FLAGS)
else ifeq ($(BUILD_MODE), Debug)
        CFLAGS = $(COMMON_FLAGS) -g
else ifeq ($(BUILD_MODE), Asan)
        CFLAGS = $(COMMON_FLAGS) -g -fsanitize=address
endif

MAIN_SERVER = sysv_server
MAIN_CLIENT = sysv_client
LIB = libshm_chat.a
SRCS = $(filter-out src/$(MAIN_SERVER).c src/$(MAIN_CLIENT).c, $(wildcard src/*.c))
OBJ := $(SRCS:.c=.o)
ifndef BUILD_DIR
	BUILD_DIR = ../build
endif

all: $(BUILD_DIR) code_check server client 

$(BUILD_DIR):
	mkdir -p $@

server: $(BUILD_DIR)/$(MAIN_SERVER).exe

client: $(BUILD_DIR)/$(MAIN_CLIENT).exe

$(BUILD_DIR)/$(MAIN_SERVER).exe: src/$(MAIN_SERVER).c $(BUILD_DIR)/$(LIB)
	@echo "\nСобираем исполняемый файл сервера. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(BUILD_DIR)/$(LIB)

$(BUILD_DIR)/$(MAIN_CLIENT).exe: src/$(MAIN_CLIENT).c $(BUILD_DIR)/$(LIB)
	@echo "\nСобираем исполняемый файл клиента. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) -o $@ $< -L. -l:$(BUILD_DIR)/$(LIB)

$(BUILD_DIR)/$(LIB): msg_lib $(BUILD_DIR)/$(LIB)($(OBJ))

msg_lib:
	@echo "\nСоздаём объектные файлы для статической библиотеки и собираем её."

code_check: $(SRCS) src/$(MAIN_SERVER).c src/$(MAIN_CLIENT).c
	-cppcheck --enable=all --suppress=missingIncludeSystem -Iinclude $^
	#-clang-format -n --style=Google $^
	clang-format -i --style=Google $^

clean:
	rm -vf *.exe *.c~ *.a *.o

.PHONY: all clean code_check msg_lib server client

