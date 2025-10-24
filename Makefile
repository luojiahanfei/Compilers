CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = your_compiler
SRC = lexer.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)