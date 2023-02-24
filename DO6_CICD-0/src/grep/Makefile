CC = gcc
FLAGS = -c -std=c11 -Wall -Werror -Wextra -D_GNU_SOURCE

all : s21_grep

s21_grep : mkdir s21_grep.o
	$(CC) ../../obj/s21_grep.o -o ./s21_grep

s21_grep.o : 
	$(CC) $(FLAGS) ./s21_grep.c -o ../../obj/s21_grep.o

mkdir :
	mkdir -p ./../../obj 

rebuild : clean 
	make all

clean : clean_obj clean_build

clean_obj :
	rm -rf ./../../obj

clean_build :
	rm ./s21_grep
