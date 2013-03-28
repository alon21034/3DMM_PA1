all: main.o Vertex.o Triangle.o ColorImage.o
	g++ -o pa1 main.o Vertex.o Triangle.o ColorImage.o

main.o: main.cpp 
	g++ -c main.cpp

Vertex.o: Vertex.cpp Vertex.h
	g++ -c Vertex.cpp

Triangle.o: Triangle.cpp Triangle.h
	g++ -c Triangle.cpp

ColorImage.o: ColorImage.cpp ColorImage.h
	g++ -c ColorImage.cpp

clean:
	rm *.o pa1