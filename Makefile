exec: main.o TreeFractal.o Sierpinski.o Renderer.o CirclePattern.o KochSnowflake.o
	g++ *.o -o exec -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

TreeFractal.o: Source/TreeFractal.cpp
	g++ -c Source/TreeFractal.cpp

KochSnowflake.o: Source/KochSnowflake.cpp
	g++ -c Source/KochSnowflake.cpp

Sierpinski.o: Source/Sierpinski.cpp
	g++ -c Source/Sierpinski.cpp

Renderer.o: Source/Renderer.cpp
	g++ -c Source/Renderer.cpp

CirclePattern.o: Source/CirclePattern.cpp
	g++ -c Source/CirclePattern.cpp
