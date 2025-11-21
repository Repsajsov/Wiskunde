CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = othello
OBJS = main.o othelloBord.o speler.o spel.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc othelloBord.h speler.h spel.h
	$(CXX) $(CXXFLAGS) -c main.cc

othelloBord.o: othelloBord.cc othelloBord.h speler.h
	$(CXX) $(CXXFLAGS) -c othelloBord.cc

speler.o: speler.cc speler.h
	$(CXX) $(CXXFLAGS) -c speler.cc

spel.o: spel.cc spel.h
	$(CXX) $(CXXFLAGS) -c spel.cc

stapel.o: stapel.cc stapel.h
	$(CXX) $(CXXFLAGS) -c stapel.cc

clean:
	rm -f $(TARGET) $(OBJS)