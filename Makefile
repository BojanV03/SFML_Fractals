exec: main.o
	g++ main.o Sierpinski.o Renderer.o CircleFractal.o -o exec -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp Source/Sierpinski.cpp Source/Renderer.cpp Source/CircleFractal.cpp
	g++ -c main.cpp Source/Sierpinski.cpp Source/Renderer.cpp Source/CircleFractal.cpp
