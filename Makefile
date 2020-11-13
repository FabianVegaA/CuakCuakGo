all: bin/tarea-2

bin/tarea-2: bin/tarea-2.o bin/graph.o
	mkdir -p bin
	gcc -o bin/tarea-2 bin/tarea-2.o bin/graph.o

bin/tarea-2.o: src/tarea-2.c src/tarea-2.h
	gcc -c src/tarea-2.c -o bin/tarea-2.o

bin/graph.o: src/graph.c src/graph.h
	gcc -c src/graph.c -o bin/graph.o

clean:
	rm -f bin/tarea-2 bin/*.o
	rm -f tarea-2 *.o