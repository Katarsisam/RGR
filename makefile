CC = g++
CFLAGS = -Wall -Wextra 

CF_CHECK = clang-format  -n
CF_APPLY = clang-format  -i
RM = rm -rf 


all : clean objects build

format : 
	$(CF_CHECK) *.c
	$(CF_CHECK) *.h
	$(CF_APPLY) *.c
	$(CF_APPLY) *.h
	
RGR: 

objects: clean C++/*.cpp 
	$(CC) $(CFLAGS) -c C++/*.cpp 
	ar rcs C++/liber.a *.o
	mv *.o C++

build: C++/liber.a C++/main.cpp
	$(CC) $(CFLAGS) C++/main.cpp C++/liber.a -o build

clean :
	$(RM) C++/*.o C++/*.a C++/*.so

rebuild : clean 