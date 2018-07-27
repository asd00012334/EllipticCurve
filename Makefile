LIB = -lgmp -lgmpxx
INC = inc

build: cleanObj
	for x in `ls src/*.cpp` ; do \
		echo $$x ;\
		y=`echo $$x | cut -d'/' -f2`; \
		z=`echo $$y | cut -d'.' -f1`; \
		g++ $$x -o obj/$$z.o -c $(LIB) -I $(INC); \
	done;

cleanObj:
	rm -f obj/*

