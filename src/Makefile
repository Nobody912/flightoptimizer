#clang++ -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function main.cpp Graph.cpp BFSTraversal.cpp json.hpp
#clang++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function main.cpp Graph.cpp BFSTraversal.cpp MapProjection.cpp Astar.cpp cs225/lodepng/lodepng.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp json.hpp 
#clang++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function test.cpp Graph.cpp BFSTraversal.cpp json.hpp
#./a.out

# CXX = clang++
# CFLAGS = -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

# SOURCES = Graph.cpp BFSTraversal.cpp MapProjection.cpp Astar.cpp cs225/lodepng/lodepng.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp json.hpp

# TARGET = main

# all: $(TARGET)

# $(TARGET): $(TARGET).cpp
# 	$(CXX) $(CFLAGS) $(TARGET) $(SOURCES)

# clean:
# 	$(RM) $(TARGET)


# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o Graph.o BFSTraversal.o MapProjection.o Astar.o

# Generated files
CLEAN_RM =  main test flightmap-test.png \
	*.o *.d cs225/*.d cs225/*.o \
	cs225/lodepng/*.o cs225/lodepng/*.d \
	json/*.o json/*.d

# Use the cs225 makefile template:
include cs225/make/cs225.mk

# MP-specific targets
OBJS = test.o Graph.o BFSTraversal.o MapProjection.o Astar.o cs225/lodepng/lodepng.o cs225/PNG.o cs225/HSLAPixel.o

test: $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

MAZE_OBJS = $(filter-out $(EXE_OBJ), $(OBJS))
