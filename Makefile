CXX = g++
CXXFLAGS = -Wall

driver: driver.o bingo.o
	$(CXX) $(CXXFLAGS) -o hello_driver hello_driver.o hello_util.o

driver.o: driver.cpp bingo.h
	$(CXX) $(CXXFLAGS) -ansi -c driver.cpp

bingo.o: bingo.cpp bingo.h
	$(CXX) $(CXXFLAGS) -ansi -c bingo.cpp

run:
	./driver
