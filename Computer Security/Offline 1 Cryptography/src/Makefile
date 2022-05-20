MAKEFLAGS += -j8

CC = g++
PARAMETERS = input.txt
# compile every cpp file in this directory with g++ , and target

# the object file in the same directory
%.o : %.cpp %.h
	${CC} -c $< -o $@

clean :
	rm -f *.o
	rm -f *.out
	rm -f *.so

.PHONY : clean

a.out : main.o
	${CC} *.o -o a.out

# run the executable
run : a.out
	./a.out ${PARAMETERS}

# compile and run
all : run

# compile and debug memory-check
memory : a.out
	valgrind --leak-check=full -s ./a.out input.txt


py : 
	g++ -c -fPIC foo.cpp -o foo.o
	g++ -shared -Wl,-soname,libfoo.so -o libfoo.so  foo.o
	python foo.py
# compile and run
.PHONY : run

# compile and run
.PHONY : all

# compile and run
.PHONY : clean

.PHONY : run