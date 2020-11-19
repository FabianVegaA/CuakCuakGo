all: bin/tarea-2 bin/bonus

# This compile the file bonus
bin/tarea-2: bin/tarea-2.o bin/graph.o bin/display.o
	mkdir -p bin
	gcc -o bin/tarea-2 -g -Wall -std=c99 bin/tarea-2.o bin/graph.o bin/display.o

bin/tarea-2.o: src/tarea-2.c src/display.h
	gcc -c -std=c11 -Wall -ggdb3 src/tarea-2.c -o bin/tarea-2.o

bin/graph.o: src/graph.c src/graph.h
	gcc -c -std=c11 -Wall -ggdb3 src/graph.c -o bin/graph.o

bin/display.o: src/display.c src/display.h
	gcc -c -std=c11 -Wall -ggdb3 src/display.c -o bin/display.o

# This compile the file bonus
bin/bonus: bin/bonus.o bin/graph.o bin/display.o
	gcc -o bin/bonus -g -Wall -std=c99  bin/bonus.o bin/graph.o bin/display.o -lm

bin/bonus.o: src/bonus.c src/display.h
	gcc -c -std=c11 -Wall -ggdb3 src/bonus.c -o bin/bonus.o 

clean:
	rm -f bin/tarea-2 bin/bonus bin/*.o
