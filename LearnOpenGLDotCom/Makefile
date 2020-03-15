all: hellotriangle.out hellowindow.out transform.out

hellotriangle.out: hellotriangle.cpp ../glad.o
	clang++ -lglfw -framework OpenGL -o hellotriangle.out hellotriangle.cpp ../glad.o

hellowindow.out: hellowindow.cpp ../glad.o
	clang++ -lglfw -framework OpenGL -o hellowindow.out hellowindow.cpp ../glad.o

transform.out: transform.cpp
	clang++ -lglfw -framework OpenGL -o transform.out transform.cpp

.PHONY: clean
clean:
	rm hellotriangle.out hellowindow.out transform.out
