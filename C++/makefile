CC = g++
CFLAGS = -Wall -Wextra 

CF_CHECK = clang-format  -n
CF_APPLY = clang-format  -i
RM = rm -rf 


all :  playfer

format : 
	$(CF_CHECK) *.c
	$(CF_CHECK) *.h
	$(CF_APPLY) *.c
	$(CF_APPLY) *.h
	
base : s21_grep.o lib.o
	$(CC) s21_grep.o lib.o -o s21_grep

enigma : s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep.o

playfer : Playfer.cpp
	$(CC) $(CFLAGS) Playfer.cpp 

	
clean :
	$(RM) *.o *.a *.so

rebuild : clean 