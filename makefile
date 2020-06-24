CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = main.o agent.o simulation.o location.o

all: abmSim

abmSim: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o $@

agent.o: agent.cpp
	$(CC) $(CFLAGS) -c agent.cpp -o $@

simulation.o: simulation.cpp
	$(CC) $(CFLAGS) -c simulation.cpp -o $@

location.o: location.cpp
	$(CC) $(CFLAGS) -c location.cpp -o $@

run:
	./abmSim

memtest:
	valgrind --leak-check=full ./abmSim

clean:
	rm $(OBJECTS) abmSim