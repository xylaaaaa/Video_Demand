# Makefile for compiling test.cpp with g++

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11
LIBS = -ljsoncpp

# Output file
OUTPUT = a
SRC = test.cpp

# Default target
all: $(OUTPUT)

# Compile the program
$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUTPUT) $(LIBS)

# Clean up
clean:
	rm -f $(OUTPUT)
