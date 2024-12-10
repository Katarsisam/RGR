CC = g++
CCX = i686-w64-mingw32-g++
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
	$(CCX) $(CFLAGS) -c C++/*.cpp 
	ar rcs C++/liber.a *.o
	mv *.o C++

build: C++/liber.a C++/main.cpp
	$(CCX) $(CFLAGS) -o build C++/main.cpp C++/liber.a -static -static-libgcc -static-libstdc++

clean :
	$(RM) -f C++/*.o C++/*.a C++/*.so

rebuild : clean 

#sudo apt install mingw-w64
#Найти у себя i686-w64-mingw32-g++ (скачать и т.д)