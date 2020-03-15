all: assignment3-rectangle.out

assignment3-rectangle.out: assignment3-rectangle.cpp ../glad.o
	clang++ -lglfw -framework OpenGL -o assignment3-rectangle.out assignment3-rectangle.cpp ../glad.o

.PHONY: clean
clean:
	rm assignment3-rectangle.out
