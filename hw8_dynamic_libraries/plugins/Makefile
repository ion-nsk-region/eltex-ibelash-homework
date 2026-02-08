CC = gcc
FLAGS = -Wall -Werror -Wextra

HEADERS = ../libs/calc.h $(wildcard *.h)

SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)
PLUGINS = $(addprefix lib,$(SRCS:.c=.so))

all: $(PLUGINS) 

msg_plugin_build:
	@echo "\nСобираем плагины"

lib%.so: %.o msg_plugin_build
	$(CC) -shared $(FLAGS) $< -o $@

msg_plugin_obj:
	@echo "\nСоздаём объектные файлы для плагинов"

%.o: %.c $(HEADERS) 
	$(CC) $(FLAGS) -fPIC -c $< -o $@

.PHONY: clean msg_plugin_obj msg_plugin_build

clean:
	@echo "\nУдаляем все сгенерированные для плагинов файлы."
	rm -vf ./*.o ./*.so
