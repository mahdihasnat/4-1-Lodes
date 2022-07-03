MAKEFLAGS += -j8

CC = g++
DIR = '../resource/Test Cases (Updated)/1
# DIR = '.
PARAMETERS = ${DIR}/scene.txt' ${DIR}/config.txt'
HEADERS = vec4.h


clean :
	rm -f *.o
	rm -f *.out
	rm -f *.so

main.out : ${HEADERS}
	${CC} main.cpp -o main.out

# run the executable
run : main.out
	./main.out ${PARAMETERS}