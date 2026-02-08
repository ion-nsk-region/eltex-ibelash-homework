CC = gcc
FLAGS = -Wall -Werror -Wextra
ARCHIVER = ar
ARCHIVER_OPTS = rc

LIB = calc
HEADERS = libs/calc.h
LIB_SRCS = $(wildcard libs/*.c)
LIB_OBJ = $(LIB_SRCS:.c=.o)

SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)

main.exe: $(SRCS) lib$(LIB).a $(HEADERS)
	@echo "\nСобираем главный исполняемый файл."
	$(CC) $(FLAGS) -o $@ $< -L. -l$(LIB) -Wl,-rpath,./plugins

msg_main_obj:
	@echo "\nСоздаём объектные файлы для основной программы"

./%.o: ./%.c $(HEADERS) msg_main_obj
	$(CC) $(FLAGS) -c $< -o $@

msg_lib_obj:
	@echo "\nСоздаём объектные файлы для статической библиотеки"

./libs/%.o: ./libs/%.c $(HEADERS) msg_lib_obj
	$(CC) $(FLAGS) -c $< -o $@

lib$(LIB).a: $(LIB_OBJ)
	@echo "\nСобираем статическую библиотеку"
	$(ARCHIVER) $(ARCHIVER_OPTS) lib$(LIB).a $(LIB_OBJ)

#TODO Запустить make в директории с плагинами

.PHONY: clean msg_lib_obj msg_main_obj 

clean:
	@echo "\nУдаляем все сгенерированные файлы."
	rm -vf *.o ./libs/*.o *.c~ *.h~ main.exe ./lib$(LIB).a
