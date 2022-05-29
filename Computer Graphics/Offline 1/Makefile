MAKEFLAGS += -j8

CC = g++
LIB = 

run: main
	./main

main :
	${CC} -o main ./src/main.cpp -lglut -lGLU -lGL
	./main
	${clean}

clean:
	rm -f main

%.o : %.cpp %.h
	${CC} -c $< -o $@