CC = g++
CFLAGS = -Wall -c -pedantic -I/usr/include/libxml2
LDFLAGS = -L/usr/local/lib -L/usr/lib
LDLIBS = -lSDL2 -lSDL2_image -lxml2

SOURCES := $(wildcard Sources/*.cpp)
OBJECTS := $(SOURCES:Sources/%.cpp=obj/%.o)

EXECUTABLE = Aurorion

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

obj/%.o: Sources/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f obj/*.o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)