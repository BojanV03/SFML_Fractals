exec: main.o Sierpinski.o Renderer.o CirclePattern.o KochSnowflake.o
	g++ main.o Sierpinski.o Renderer.o CirclePattern.o KochSnowflake.o -o exec -lsfml-graphics -lsfml-window -lsfml-system

KochSnowflake.o: Source/KochSnowflake.cpp
	g++ -c Source/KochSnowflake.cpp

Sierpinski.o: Source/Sierpinski.cpp
	g++ -c Source/Sierpinski.cpp

Renderer.o: Source/Renderer.cpp
	g++ -c Source/Renderer.cpp

CirclePattern.o: Source/CirclePattern.cpp
	g++ -c Source/CirclePattern.cpp

main.o: main.cpp
	g++ -c main.cpp
