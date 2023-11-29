main.exe: main.o NN.o
	g++ -o main.exe main.o NN.o

main.o: main.cpp NN.cpp NN.h
	g++ -c main.cpp

NN.o: NN.cpp NN.h
	g++ -c NN.cpp

debug:
	g++ -g -o mainDebug.exe main.o NN.o
	gdb mainDebug.exe

clean:
	rm -f *.exe *.o *.stackdump *~ out.txt

run:
	make
	./main.exe
