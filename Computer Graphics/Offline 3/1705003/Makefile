MAKEFLAGS += -j8

CC = g++
LIB = -lglut -lGLU -lGL

run: main.out
	# valgrind --leak-check=full ./main.out
	./main.out

main.out : *.cpp *.h
	${CC} -o main.out 1705003_main.cpp -lglut -lGLU -lGL -Ofast -Og

clean:
	rm -f main.out *.bmp
	

# %.o : %.cpp %.h
# 	${CC} -c $< -o $@

# Grep to find every import
# grep "#include \".*\"" *.h