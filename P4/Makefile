CC=g++
CFLAGS=-std=c++11 -Werror
TARGET = comp
OBJS = main.o scanner.o parser.o node.o static_semantics.o stack.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.cpp parser.h token.h node.h static_semantics.h
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: scanner.cpp token.h scanner.h parser.h
	$(CC) $(CFLAGS) -c scanner.cpp

parser.o: parser.cpp node.h token.h scanner.h parser.h
	$(CC) $(CFLAGS) -c parser.cpp

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp

static_semantics.o: static_semantics.cpp token.h static_semantics.h stack.h
	$(CC) $(CFLAGS) -c static_semantics.cpp

stack.o: stack.cpp stack.h
	$(CC) $(CFLAGS) -c stack.cpp

clean:
	rm $(TARGET) *.o TEMPOUT 
