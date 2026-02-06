CC = gcc
FLAGS = -Wall -Werror -Wextra

LIB = calc
HEADERS = ../libs/calc.h $(wildcard *.h)

SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)

msg_plugin_obj:
	@echo "\nСоздаём объектные файлы для плагинов"

%.o: %.c $(HEADERS) msg_plugin_obj
	$(CC) $(FLAGS) -fPIC -c $< -o $@

msg_plugin_build:
	@echo "\nСобираем плагины"

lib%.so: %.o %.h msg_plugin_build
	$(CC) -shared $(FLAGS) $< -o $@

.PHONY: clean msg_plugin_obj msg_plugin_build

clean:
	@echo "\nУдаляем все сгенерированные для плагинов файлы."
	rm -vf ./*.o ./*.so
