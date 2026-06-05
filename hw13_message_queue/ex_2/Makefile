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


SRC_DIR = src
BUILD_DIR = build
LIB_DIR = lib

MAIN_SERVER = server
SERVER_LIBS = -pthread
SERVER_SRCS = $(wildcard $(SRC_DIR)/server/*.c)
SERVER_OBJ := $(patsubst $(SRC_DIR)/server/%.c, $(BUILD_DIR)/%.o, $(SERVER_SRCS))

MAIN_CLIENT = client
CLIENT_LIBS = -lncursesw -pthread
CLIENT_SRCS = $(wildcard $(SRC_DIR)/client/*.c)
CLIENT_OBJ := $(patsubst $(SRC_DIR)/client/%.c, $(BUILD_DIR)/%.o, $(CLIENT_SRCS))

LIB_NAME = mq_chat
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
LIB_SRCS = $(wildcard $(SRC_DIR)/common/*.c)
LIB_OBJ := $(patsubst $(SRC_DIR)/common/%.c, $(BUILD_DIR)/%.o, $(LIB_SRCS))
LDFLAGS = -L$(LIB_DIR) -l$(LIB_NAME)

all: code_check directories server client 

directories: $(BUILD_DIR) $(LIB_DIR)

$(BUILD_DIR):
	mkdir -p $@ 
	
$(LIB_DIR):
	mkdir -p $@

server: $(BUILD_DIR)/$(MAIN_SERVER).exe

client: $(BUILD_DIR)/$(MAIN_CLIENT).exe

$(BUILD_DIR)/$(MAIN_SERVER).exe: $(SERVER_SRCS) $(STATIC_LIB)
	@echo "\nСобираем исполняемый файл сервера. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $@ $(SERVER_LIBS) $(LDFLAGS)

$(BUILD_DIR)/$(MAIN_CLIENT).exe: $(CLIENT_SRCS) $(STATIC_LIB)
	@echo "\nСобираем исполняемый файл клиента. Флаги компиляции: $(CFLAGS)"
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $@ $(CLIENT_LIBS) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/common/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(LIB_OBJ) 
	@echo "\nСобираем статическую библиотеку."
	ar rcs $@ $^

code_check: $(SERVER_SRCS) $(SRC_DIR)/server/$(MAIN_SERVER).c $(CLIENT_SRCS) $(SRC_DIR)/client/$(MAIN_CLIENT).c $(LIB_SRCS)
	-cppcheck --enable=all --suppress=missingIncludeSystem -Iinclude $^
	#-clang-format -n --style=Google -Iinclude $^
	clang-format -i --style=Google $^

clean:
	rm -vrf $(BUILD_DIR) $(LIB_DIR)

.PHONY: all clean code_check server client directories

