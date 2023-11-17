main.exe: main.o NN.o
	g++ -o main.exe main.o NN.o

main.o: main.cpp NN.h
	g++ -c main.cpp

NN.o: NN.cpp NN.h
	g++ -c NN.cpp
	
clean:
	rm -f *.exe *.o *.stackdump *~ out.txt

run:
	make
	./main.exe
