all: hoofd.o othellobord.o 
	g++ -Wall -Wextra -o hetspel othellobord.o hoofd.o 

othellobord.o: othellobord.cc othellobord.h
	g++ -Wall -Wextra -c othellobord.cc 

hoofd.o: hoofd.cc othellobord.h 
	g++ -Wall -Wextra -c hoofd.cc 

clean:
	rm -f *.o hetspel 