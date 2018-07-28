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
	$(GCC) $(INC) test.cpp $(OBJ) -o test $(LIB)

clean:
	rm -f test
