CXX = g++
FLAGS = -O3


all: src/main.cpp src/Integer.cpp src/yenck.cpp
	$(CXX) $(FLAGS) $^ -o bin/main

run: bin/main
	bin/main

test: test/test.sh bin/main
	test/test.sh
