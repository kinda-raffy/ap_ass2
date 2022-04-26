CC=g++
CCOPTS=-Wall -Werror -g -O -std=c++14
# CCOPTS=-g -O -std=c++14

OBJECTS=$(shell find *.cpp | sed 's/.cpp/.o/g')

OUTPUT=scrabble

all: $(OUTPUT)

clean: testclean
	rm -f $(OUTPUT) *.o

$(OUTPUT): $(OBJECTS)
	$(CC) $(CCOPTS) -o $(OUTPUT) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CCOPTS) -c $^

%.cpp:
