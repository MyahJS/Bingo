CXX = g++
CXXFLAGS = -W -g

driver: driver.cpp bingo.cpp 
	$(CXX) $(CXXFLAGS) driver.cpp bingo.cpp -o driver 

run:
	./driver
