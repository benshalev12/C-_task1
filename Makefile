CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++11

all: main

main: main.o graph.o algorithms.o
	$(CXX) $(CXXFLAGS) -o main main.o graph.o algorithms.o

main.o: main.cpp graph.hpp algorithms.hpp queue.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

graph.o: graph.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

algorithms.o: algorithms.cpp algorithms.hpp graph.hpp queue.hpp
	$(CXX) $(CXXFLAGS) -c algorithms.cpp

clean:
	rm -f *.o main

test: test_doctest.o graph.o algorithms.o
	$(CXX) $(CXXFLAGS) -o test test_doctest.o graph.o algorithms.o
	./test

test_doctest.o: test_doctest.cpp graph.hpp algorithms.hpp queue.hpp doctest.h
	$(CXX) $(CXXFLAGS) -c test_doctest.cpp


valgrind: test
	valgrind --leak-check=full --track-origins=yes ./test