CC = gcc
FLAGS = -Wall -Werror -Wextra

LIB = calc
HEADERS = libs/calc.h
LIB_SRCS = $(wildcard libs/*.c)
LIB_OBJ = $(LIB_SRCS:.c=.o)

SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)

main.exe: $(SRCS) lib$(LIB).so $(HEADERS)
	@echo "\nСобираем главный исполняемый файл."
	$(CC) $(FLAGS) -o $@ $< -L. -l$(LIB) -Wl,-rpath,./,-rpath,./libs

msg_lib_obj:
	@echo "\nСоздаём объектные файлы для динамической библиотеки"

./libs/%.o: ./libs/%.c $(HEADERS) msg_lib_obj
	$(CC) $(FLAGS) -fPIC -c $< -o $@

msg_main_obj:
	@echo "\nСоздаём объектные файлы для основной программы"

./%.o: ./%.c $(HEADERS) msg_main_obj
	$(CC) $(FLAGS) -c $< -o $@

lib$(LIB).so: $(LIB_OBJ)
	@echo "\nСобираем динамическую библиотеку"
	$(CC) -shared $(FLAGS) $(LIB_OBJ) -o lib$(LIB).so

.PHONY: clean msg_lib_obj msg_main_obj

clean:
	@echo "\nУдаляем все сгенерированные файлы."
	rm -vf *.o ./libs/*.o *.c~ *.h~ main.exe ./lib$(LIB).so
