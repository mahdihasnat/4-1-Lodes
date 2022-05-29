MAKEFLAGS += -j8

CC = g++
LIB = 

run: main
	./main

main : ./src/main.cpp ./src/inputListener.h ./src/point.h
	${CC} -o main ./src/main.cpp -lglut -lGLU -lGL

clean:
	rm -f main

%.o : %.cpp %.h
	${CC} -c $< -o $@