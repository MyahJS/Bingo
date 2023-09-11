CXX = g++
CXXFLAGS = -W -g

mytest: mytest.cpp bingo.cpp 
	$(CXX) $(CXXFLAGS) mytest.cpp bingo.cpp -o mytest

run:
	./mytest
