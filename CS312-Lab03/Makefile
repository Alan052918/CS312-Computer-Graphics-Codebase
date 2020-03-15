all: assignment3-cube.out assignment3-rectangle.out

assignment3-cube.out: assignment3-cube.cpp ../glad.o
	clang++ -lglfw -framework OpenGL -o assignment3-cube.out assignment3-cube.cpp ../glad.o

assignment3-rectangle.out: assignment3-rectangle.cpp ../glad.o
	clang++ -lglfw -framework OpenGL -o assignment3-rectangle.out assignment3-rectangle.cpp ../glad.o

.PHONY: clean
clean:
	rm assignment3-cube.out assignment3-rectangle.out
