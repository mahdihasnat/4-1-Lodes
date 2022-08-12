MAKEFLAGS += -j8

CC = g++
LIB = -lglut -lGLU -lGL

run: main.out
	./main.out

main.out : main.cpp inputListener.h point.h draw.h object.h
	${CC} -o main.out main.cpp -lglut -lGLU -lGL

clean:
	rm -f main.o

# %.o : %.cpp %.h
# 	${CC} -c $< -o $@