CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = testing.o PetData.o

all: testingThing

testingThing: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

testing.o: testing.cpp
	$(CC) $(CFLAGS) -c testing.cpp -o $@

PetData.o: PetData.cpp
	$(CC) $(CFLAGS) -c PetData.cpp -o $@

run:
	./testingThing

memtest:
	valgrind --leak-check=full ./testingThing

clean:
	rm $(OBJECTS) testingThing