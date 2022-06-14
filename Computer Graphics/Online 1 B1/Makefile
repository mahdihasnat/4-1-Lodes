MAKEFLAGS += -j8

CC = g++
LIB = 

run: main.o main2.o
	./main2.o

main.o : ./main.cpp ./inputListener.h ./point.h ./draw.h
	${CC} -o main.o ./main.cpp -lglut -lGLU -lGL

main2.o : ./main2.cpp ./inputListener2.h ./point.h ./draw2.h
	${CC} -o main2.o ./main2.cpp -lglut -lGLU -lGL

clean:
	rm -f main.o
	rm -f main2.o

# %.o : %.cpp %.h
# 	${CC} -c $< -o $@