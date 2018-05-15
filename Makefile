CXX = g++
FLAGS = -O3
INC = -I ./inc/

RM = rm -f

all: src/main.cpp src/Integer.cpp src/yenck.cpp
	$(CXX) $(FLAGS) $(INC) $^ -o bin/main

run: bin/main
	bin/main

test: test/test.sh bin/main
	test/test.sh

clean:
	$(RM) bin/main
