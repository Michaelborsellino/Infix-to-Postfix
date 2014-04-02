all: in2post.x

in2post.x: in2post.o
	g++47 -o in2post.x in2post.o
in2post.o: in2post.cpp
	g++47 -g -c -Wall -Wextra -std=c++11 in2post.cpp
clean:
	rm *.o in2post.x

