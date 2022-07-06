main: main.cpp graph.o heap.o
	g++ graph.o heap.o main.cpp -o main -g

graph.o: graph.cpp
	g++ graph.cpp -c

heap.o: heap.cpp
	g++ heap.cpp -c

clean:
	rm *.o
