# COVID-19ABMGuelphS20
# 26/06/20
# ver 0.01
#
# Makefile for the COVID-19 eABM

SRCDIR = ./src/
BINDIR = ./bin/
INCDIR = ./include/

CC = g++
CFLAGS = -std=c++11 -Wall -I./include
OBJECTS = $(BINDIR)main.o $(BINDIR)agent.o $(BINDIR)simulation.o $(BINDIR)location.o

all: $(BINDIR)abmSim

$(BINDIR)abmSim: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(BINDIR)main.o: $(SRCDIR)main.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)main.cpp -o $@

$(BINDIR)agent.o: $(SRCDIR)agent.cpp $(INCDIR)agent.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)agent.cpp -o $@

$(BINDIR)simulation.o: $(SRCDIR)simulation.cpp $(INCDIR)simulation.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)simulation.cpp -o $@

$(BINDIR)location.o: $(SRCDIR)location.cpp $(INCDIR)location.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)location.cpp -o $@

run:
	$(BINDIR)abmSim

memtest:
	valgrind --leak-check=full $(BINDIR)abmSim

clean:
	rm $(OBJECTS) $(BINDIR)abmSim