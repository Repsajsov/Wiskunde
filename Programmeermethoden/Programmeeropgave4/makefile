CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = othello
OBJS = main.o othelloBord.o speler.o inputHandler.o overige.o stapel.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc othelloBord.h speler.h inputHandler.h overige.h
	$(CXX) $(CXXFLAGS) -c main.cc

othelloBord.o: othelloBord.cc othelloBord.h speler.h overige.h
	$(CXX) $(CXXFLAGS) -c othelloBord.cc

speler.o: speler.cc speler.h
	$(CXX) $(CXXFLAGS) -c speler.cc

inputHandler.o: inputHandler.cc inputHandler.h overige.h
	$(CXX) $(CXXFLAGS) -c inputHandler.cc

overige.o: overige.cc overige.h
	$(CXX) $(CXXFLAGS) -c overige.cc

stapel.o: stapel.cc stapel.h
	$(CXX) $(CXXFLAGS) -c stapel.cc

clean:
	rm -f $(TARGET) $(OBJS)