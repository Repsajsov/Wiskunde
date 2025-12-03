all: hoofd.o othellobord.o stapel.o
	g++ -Wall -Wextra -o hetspel othellobord.o stapel.o hoofd.o 2>> warnings.txt

othellobord.o: othellobord.cc othellobord.h
	g++ -Wall -Wextra -c othellobord.cc 2> warnings.txt

hoofd.o: hoofd.cc othellobord.h stapel.h
	g++ -Wall -Wextra -c hoofd.cc 2>> warnings.txt

stapel.o: stapel.cc stapel.h
	g++ -Wall -Wextra -c stapel.cc 2>> warnings.txt

clean:
	rm -f *.o hetspel warnings.txt