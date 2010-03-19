CC=g++
CFLAGS=-c -Wall -I../
LDFLAGS=
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=igloo-tests.exe

all: test

test: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm *.o *.exe

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
	
.PHONY: all test clean
