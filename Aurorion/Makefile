CC = g++
CFLAGS = -Wall -std=c++17 -c -g -pedantic -O3
LDLIBS = -lSDL2 -lSDL2_image -lxml2
INCLUDES = $(shell pkg-config --cflags libxml-2.0)

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)

EXECUTABLE = Aurorion

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f obj/*.o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(MODE)

deps:
	$(CC) -MM $(SOURCES) > Makefile.d

-include Makefile.d
