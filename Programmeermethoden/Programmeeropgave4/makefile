CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = othello

OBJS = main.o othelloBord.o spel.o speler.o stapel.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc spel.h
	$(CXX) $(CXXFLAGS) -c main.cc

othelloBord.o: othelloBord.cc othelloBord.h speler.h spel.h
	$(CXX) $(CXXFLAGS) -c othelloBord.cc

spel.o: spel.cc spel.h othelloBord.h speler.h stapel.h
	$(CXX) $(CXXFLAGS) -c spel.cc

speler.o: speler.cc speler.h
	$(CXX) $(CXXFLAGS) -c speler.cc

stapel.o: stapel.cc stapel.h othelloBord.h speler.h
	$(CXX) $(CXXFLAGS) -c stapel.cc

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean