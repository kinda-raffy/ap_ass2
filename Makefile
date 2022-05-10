CC=g++
CCOPTS=-Wall -Werror -g -O -std=c++14
# CCOPTS=-g -O -std=c++14

OBJECTS=$(shell find *.cpp | sed 's/.cpp/.o/g')
HAOBJECTS=scrabble.cpp LinkedList.cpp Node.cpp Tile.cpp Board.cpp Core.cpp Player.cpp TileBag.cpp
OUTPUT=scrabble

all: $(OUTPUT)

clean:
	rm -f $(OUTPUT) *.o

$(OUTPUT): $(OBJECTS)
	$(CC) $(CCOPTS) -o $(OUTPUT) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CCOPTS) -c $^

%.cpp:

# g++ -Wall -Werror -g -O -std=c++14 -o
# haDebug haDebug.cpp Board.cpp LinkedList.cpp Node.cpp SaveState.cpp
haDebug:
	$(CC) $(CCOPTS) -o haDebug $(HAOBJECTS)

haDebugClean:
	rm -f haDebug
