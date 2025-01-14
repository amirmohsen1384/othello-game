CC=x86_64-w64-mingw32-g++

all: main

main: coordinates.o game.o point.o render.o system.o table.o text.o
	$(CC) -o "othello.exe" coordinates.o game.o point.o render.o system.o table.o text.o main.cpp

coordinates.o:
	$(CC) -o coordinates.o -c src/coordinates.cpp

game.o:
	$(CC) -o game.o -c src/game.cpp

render.o:
	$(CC) -o render.o -c src/render.cpp

system.o:
	$(CC) -o system.o -c src/system.cpp

table.o:
	$(CC) -o table.o -c src/table.cpp

text.o:
	$(CC) -o text.o -c src/text.cpp

point.o:
	$(CC) -o point.o -c src/point.cpp

clean:
	rm *.o
