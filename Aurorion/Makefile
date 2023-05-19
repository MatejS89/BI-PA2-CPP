CC = g++
CFLAGS = -Wall -c -g -pedantic
LDLIBS = -lSDL2 -lSDL2_image -lxml2
INCLUDES = -I/usr/include/libxml2

SOURCES := $(wildcard Sources/*.cpp)
OBJECTS := $(SOURCES:Sources/%.cpp=obj/%.o)

EXECUTABLE = Aurorion

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS)

obj/%.o: Sources/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f obj/*.o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)