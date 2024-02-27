all: main

main: main.cpp
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
