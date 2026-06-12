ifndef BUILD_MODE
    BUILD_MODE = Release
endif

COMMON_FLAGS = -Wall -Wextra -Werror

ifeq ($(BUILD_MODE), Release)
        CFLAGS = $(COMMON_FLAGS)
else ifeq ($(BUILD_MODE), Debug)
        CFLAGS = $(COMMON_FLAGS) -g 
else ifeq ($(BUILD_MODE), Asan)
        CFLAGS = $(COMMON_FLAGS) -g -fsanitize=address
endif

BUILD_DIR = build
EX1_DIR = ex_1
EX2_DIR = ex_2
EX3_DIR = ex_3

all: code_check ex_1

ex_1: $(BUILD_DIR) receiver1 sender

ex_2: $(BUILD_DIR) receiver2

ex_3: $(BUILD_DIR) receiver3

sender: $(BUILD_DIR)/sender.exe

$(BUILD_DIR)/sender.exe: $(EX1_DIR)/signal_sender.c
	$(CC) $(CFLAGS) $^ -o $@

# Первый ======================================================
receiver1: $(BUILD_DIR)/receiver1.exe

$(BUILD_DIR)/receiver1.exe: $(EX1_DIR)/signal_receiver.c $(EX1_DIR)/signal_receiver.h $(EX1_DIR)/signal_handler.c
	$(CC) $(CFLAGS) $^ -o $@

# Второй ======================================================
receiver2: $(BUILD_DIR)/receiver2.exe

$(BUILD_DIR)/receiver2.exe: $(EX2_DIR)/signal_receiver2.c $(EX2_DIR)/signal_receiver2.h
	$(CC) $(CFLAGS) $^ -o $@

# Третий ======================================================
receiver3: $(BUILD_DIR)/receiver3.exe

$(BUILD_DIR)/receiver3.exe: $(EX3_DIR)/signal_receiver.c $(EX3_DIR)/signal_receiver.h
	$(CC) $(CFLAGS) $^ -o $@

# =============================================================

code_check: $(EX1_DIR)/*.c $(EX2_DIR)/*.c
	clang-format -i --style=Google $^
	-cppcheck --enable=all --suppress=missingIncludeSystem $^

$(BUILD_DIR):
	mkdir -p $@

clean:
	find -name "*~" -delete
	rm -rvf build

.PHONY: all receiver sender code_check clean ex_1 ex_2 ex_3
