all: bin/tarea-2

bin/tarea-2: bin/tarea-2.o bin/graph.o
	mkdir -p bin
	gcc -o bin/tarea-2 bin/tarea-2.o bin/graph.o

bin/tarea-2.o: src/tarea-2.c src/tarea-2.h
	gcc -c src/tarea-2.c -o bin/tarea-2.o

bin/graph.o: src/graph.c src/graph.h
	gcc -c src/graph.c -o bin/graph.o

bin/bonus: bin/bonus.o bin/graph.o
	gcc -o bin/bonus bin/bonus.o bin/graph.o

bin/bonus.o: src/bonus.c src/bonus.h
	gcc -c src/bonus.c -o bin/bonus.o

clean:
	rm -f bin/tarea-2 bin/*.o
