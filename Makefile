# Defines required variables.
CC=x86_64-w64-mingw32-g++
APP=othello.exe
CXXFLAGS= -g -O0

# Checks whether debugging is applied or not.
DEBUG ?= 0

ifeq ($(DEBUG), 1)
	CXXFLAGS= -g -O0
else
	CXXFLAGS= -O2
endif

all: main

# Defines the main target and the list of object files.
# Windows-specific libraries needs to be linked.
main: container.o game.o point.o render.o system.o table.o text.o io.o match.o
	$(CC) $(CXXFLAGS) -o $(APP) *.o main.cpp

container.o:
	$(CC) $(CXXFLAGS) -o container.o -c src/container.cpp

game.o:
	$(CC) $(CXXFLAGS) -o game.o -c src/game.cpp

match.o:
	$(CC) $(CXXFLAGS) -o match.o -c src/match.cpp
	
render.o:
	$(CC) $(CXXFLAGS) -o render.o -c src/render.cpp

system.o:
	$(CC) $(CXXFLAGS) -o system.o -c src/system.cpp

table.o:
	$(CC) $(CXXFLAGS) -o table.o -c src/table.cpp

text.o:
	$(CC) $(CXXFLAGS) -o text.o -c src/text.cpp

point.o:
	$(CC) $(CXXFLAGS) -o point.o -c src/point.cpp

io.o:
	$(CC) $(CXXFLAGS) -o io.o -c src/io.cpp

clean:
	@rm *.o
	@rm $(APP)