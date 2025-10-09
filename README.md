CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = sphere_points
SOURCES = main.cpp point3d.cpp spheregenerator.cpp filemanager.cpp menu.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) points.txt visualize.py

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
