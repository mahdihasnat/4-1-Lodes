MAKEFLAGS += -j8

CC = g++
LIB = 

run: main.o main2.o
	./main2.o

main.o : ./src/main.cpp ./src/inputListener.h ./src/point.h ./src/draw.h
	${CC} -o main.o ./src/main.cpp -lglut -lGLU -lGL

main2.o : ./src/main2.cpp ./src/inputListener2.h ./src/point.h ./src/draw2.h
	${CC} -o main2.o ./src/main2.cpp -lglut -lGLU -lGL

clean:
	rm -f main.o
	rm -f main2.o

# %.o : %.cpp %.h
# 	${CC} -c $< -o $@