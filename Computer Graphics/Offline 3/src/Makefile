MAKEFLAGS += -j8

CC = g++
LIB = -lglut -lGLU -lGL

run: main.out
	# valgrind --leak-check=full ./main.out
	./main.out

main.out : *.cpp *.h
	${CC} -o main.out main.cpp -lglut -lGLU -lGL -Ofast -Og

clean:
	rm -f main.out *.bmp

build:
	cat constants.h \
color.h \
vec4.h \
vec3.h \
ray.h \
object.h \
triangle.h \
generalQuadraticSurface.h \
floor.h \
sphere.h \
light.h \
pointLight.h \
spotLight.h \
mat4.h \
common.h \
variables.h \
draw.h \
bitmap_image.hpp \
capture.h \
inputListener.h \
main.cpp > 1705003.h
	

# %.o : %.cpp %.h
# 	${CC} -c $< -o $@

# Grep to find every import
# grep "#include \".*\"" *.h