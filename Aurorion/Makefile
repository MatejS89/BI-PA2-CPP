.PHONY: all
all:
# Compiler)
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wpedantic

# Libraries to link
LIBS = -lSDL2 -lSDL2_image

# Source files
SRCS = $(wildcard Sources/*.cpp)

# Object files
OBJS = $(SRCS:Sources/%.cpp=obj%.o)

OBJ_NAME = a.out

all: $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) $(LIBS) -o $(OBJ_NAME)

run: a.out
	./a.out