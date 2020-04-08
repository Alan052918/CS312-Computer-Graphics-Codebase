all: assignment5-moving-square.out quiz.out

assignment5-moving-square.out: assignment5-moving-square.cpp ../glad.o
	g++ -lglfw -framework OpenGL -o assignment5-moving-square.out assignment5-moving-square.cpp ../glad.o

quiz.out: quiz.cpp ../glad.o
	g++ -lglfw -framework OpenGL -o quiz.out quiz.cpp ../glad.o

.PHONY: clean
clean:
	rm assignment5-moving-square.out quiz.out
