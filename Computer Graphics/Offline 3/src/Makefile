MAKEFLAGS += -j8

CC = g++
LIB = -lglut -lGLU -lGL

run: main.out
	./main.out

main.out : *.cpp *.h
	${CC} -o main.out main.cpp -lglut -lGLU -lGL

clean:
	rm -f main.out

# %.o : %.cpp %.h
# 	${CC} -c $< -o $@