CC=x86_64-w64-mingw32-g++
APP=othello.exe

all: main

main: coordinates.o game.o point.o render.o system.o table.o text.o io.o
	$(CC) -o $(APP) coordinates.o game.o point.o render.o system.o table.o text.o io.o main.cpp
	@rm *.o

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

io.o:
	$(CC) -o io.o -c src/io.cpp

clean:
	@rm *.o
	@rm $(APP)