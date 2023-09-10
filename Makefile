CXX = g++
CXXFLAGS = -Wall

driver: driver.o bingo.o
	$(CXX) $(CXXFLAGS) -o driver driver.o bingo.o

driver.o: driver.cpp bingo.h
	$(CXX) $(CXXFLAGS) driver.cpp

bingo.o: bingo.cpp bingo.h
	$(CXX) $(CXXFLAGS) bingo.cpp

run:
	./driver
