CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = othello
OBJS = main.o othelloBord.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc othelloBord.h
	$(CXX) $(CXXFLAGS) -c main.cc

othelloBord.o: othelloBord.cc othelloBord.h
	$(CXX) $(CXXFLAGS) -c othelloBord.cc

clean:
	rm -f $(TARGET) $(OBJS)