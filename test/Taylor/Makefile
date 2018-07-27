GCC = g++ -std=c++14
LIB = -lgmp -lgmpxx
INC = -I ../../inc
OBJ = ../../obj/*.o

test: build
	./test
	make clean

build:
	ls $(OBJ)
	make -C ../../ build
	$(GCC) $(LIB) $(INC) $(OBJ) test.cpp -o test

clean:
	rm -f test
