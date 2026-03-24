CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard *.c)


all: code_check $(SRCS:.c=.exe)

%.exe: %.c
	clang-format -i --style=Google $<
	$(CC) $(CFLAGS) -o $@ $<

code_check: $(SRCS)
	-cppcheck --enable=all --suppress=missingIncludeSystem $^
	-clang-format -n --style=Google $^

clean:
	rm -vf *.exe

.PHONY: all clean code_check
