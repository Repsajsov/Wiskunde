CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = othello

OBJS = main.o othelloBord.o spel.o speler.o stapel.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) 2>&1 | tee compile.log

main.o: main.cc spel.h
	$(CXX) $(CXXFLAGS) -c main.cc 2>&1 | tee -a compile.log

othelloBord.o: othelloBord.cc othelloBord.h speler.h spel.h
	$(CXX) $(CXXFLAGS) -c othelloBord.cc 2>&1 | tee -a compile.log

spel.o: spel.cc spel.h othelloBord.h speler.h stapel.h
	$(CXX) $(CXXFLAGS) -c spel.cc 2>&1 | tee -a compile.log

speler.o: speler.cc speler.h
	$(CXX) $(CXXFLAGS) -c speler.cc 2>&1 | tee -a compile.log

stapel.o: stapel.cc stapel.h othelloBord.h speler.h
	$(CXX) $(CXXFLAGS) -c stapel.cc 2>&1 | tee -a compile.log

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean