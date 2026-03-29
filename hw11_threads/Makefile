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

SRCS = $(wildcard *.c)


all: code_check $(SRCS:.c=.exe)

%.exe: %.c
	clang-format -i --style=Google $<
	$(CC) $(CFLAGS) -o $@ $<

code_check: $(SRCS)
	-cppcheck --enable=all --suppress=missingIncludeSystem $^
	#-clang-format -n --style=Google $^

clean:
	rm -vf *.exe *.c~

.PHONY: all clean code_check
