all: assignment3-rectangle.out assignment3-triangle.out

assignment3-rectangle.out: assignment3-rectangle.cpp ../glad.o
	g++ -lglfw -framework OpenGL -o assignment3-rectangle.out assignment3-rectangle.cpp ../glad.o

assignment3-triangle.out: assignment3-triangle.cpp ../glad.o
	g++ -lglfw -framework OpenGL -o assignment3-triangle.out assignment3-triangle.cpp ../glad.o

.PHONY: clean
clean:
	rm assignment3-rectangle.out assignment3-triangle.out
