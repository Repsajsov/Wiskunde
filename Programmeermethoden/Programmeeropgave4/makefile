CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = othello

all: $(TARGET)

$(TARGET): main.cc
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cc

clean:
	rm -f $(TARGET)