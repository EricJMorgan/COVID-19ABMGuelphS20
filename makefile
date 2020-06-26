CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = main.o agent.o simulation.o location.o
SRC = src/

all: abmSim

abmSim: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

main.o: $(SRC)main.cpp
	$(CC) $(CFLAGS) -c $(SRC)main.cpp -o $@

agent.o: $(SRC)agent.cpp
	$(CC) $(CFLAGS) -c $(SRC)agent.cpp -o $@

simulation.o: $(SRC)simulation.cpp
	$(CC) $(CFLAGS) -c $(SRC)simulation.cpp -o $@

location.o: $(SRC)location.cpp
	$(CC) $(CFLAGS) -c $(SRC)location.cpp -o $@

run:
	./abmSim

memtest:
	valgrind --leak-check=full ./abmSim

clean:
	rm $(OBJECTS) abmSim