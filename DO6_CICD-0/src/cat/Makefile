CC = gcc
FLAGS = -c -std=c11 -Wall -Werror -Wextra -D_GNU_SOURCE

all : s21_cat

s21_cat : mkdir s21_cat.o
	$(CC) ../../obj/s21_cat.o -o ./s21_cat

s21_cat.o : 
	$(CC) $(FLAGS) ./s21_cat.c -o ../../obj/s21_cat.o

mkdir :
	mkdir -p ./../../obj 

rebuild : clean 
	make all

clean : clean_obj clean_build

clean_obj :
	rm -rf ./../../obj

clean_build :
	rm ./s21_cat
