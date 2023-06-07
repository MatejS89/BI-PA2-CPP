CXXFLAGS = -Wall -pedantic -std=c++17

LDLIBS = -lSDL2 -lSDL2_image -lxml2
INCLUDES = -I/usr/include/libxml2 -I/usr/include/SDL2
HEADERS = $(wildcard src/*.h src/*.hpp)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./sedlam53 $(MODE)

.PHONY: compile
compile: sedlam53

sedlam53: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@ $(LDLIBS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $(INCLUDES) $< -c -o $@
.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf sedlam53 build/ doc/
