MAKEFLAGS += -j8

CC = g++
LIB = 

run: main.o
	./main.o

main.o : ./src/main.cpp ./src/inputListener.h ./src/point.h
	${CC} -o main.o ./src/main.cpp -lglut -lGLU -lGL

clean:
	rm -f main.o

# %.o : %.cpp %.h
# 	${CC} -c $< -o $@