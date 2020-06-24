CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = agent.o simulation.o

all: abmSim

abmSim: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

agent.o: agent.cpp
	$(CC) $(CFLAGS) -c agent.cpp -o $@

simulation.o: simulation.cpp
	$(CC) $(CFLAGS) -c simulation.cpp -o $@

run:
	./abmSim

memtest:
	valgrind --leak-check=full ./abmSim

clean:
	rm $(OBJECTS) abmSim