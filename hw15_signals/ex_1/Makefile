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

all: code_check receiver sender

receiver: receiver.exe

receiver.exe: signal_receiver.c signal_receiver.h signal_handler.c
	$(CC) $(CFLAGS) $^ -o $@

sender: sender.exe

sender.exe: signal_sender.c
	$(CC) $(CFLAGS) $^ -o $@

code_check: *.c
	clang-format -i --style=Google $^
	-cppcheck --enable=all --suppress=missingIncludeSystem $^

clean:
	rm -vf *.exe

.PHONY: all receiver sender code_check clean
