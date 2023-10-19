# Makefile

# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra
# Source files
SOURCES := main.cpp Tasks.cpp
# Object files (derived from source files)
OBJECTS := $(SOURCES:.cpp=.o)
# Executable name
EXECUTABLE := toDoList

# Default rule
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	
