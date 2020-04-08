all: assignment5-moving-camera.out quiz.out

assignment5-moving-camera.out: assignment5-moving-camera.cpp ../glad.o
	g++ -lglfw -framework OpenGL -o assignment5-moving-camera.out assignment5-moving-camera.cpp ../glad.o

quiz.out: quiz.cpp ../glad.o
	g++ -lglfw -framework OpenGL -o quiz.out quiz.cpp ../glad.o

.PHONY: clean
clean:
	rm assignment5-moving-camera.out quiz.out
