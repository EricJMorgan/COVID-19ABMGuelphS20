# COVID-19ABMGuelphS20
# 07/07/20
# ver 0.02
#
# Makefile for the COVID-19 eABM

SRCDIR = ./src/
BINDIR = ./bin/
INCDIR = ./include/

CC = g++
CFLAGS = -std=c++11 -Wall -I./include

OBJECTS = $(BINDIR)main.o $(BINDIR)agent.o $(BINDIR)simulation.o $(BINDIR)location.o $(BINDIR)postalCode.o $(BINDIR)SIR.o $(BINDIR)SIRtotals.o $(BINDIR)transportation.o $(BINDIR)business.o $(BINDIR)geographicalrisk.o $(BINDIR)hospital.o $(BINDIR)isolationcompartment.o

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

$(BINDIR)postalCode.o: $(SRCDIR)postalCode.cpp $(INCDIR)postalCode.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)postalCode.cpp -o $@

$(BINDIR)SIR.o: $(SRCDIR)SIR.cpp $(INCDIR)SIR.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)SIR.cpp -o $@

$(BINDIR)SIRtotals.o: $(SRCDIR)SIRtotals.cpp $(INCDIR)SIRtotals.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)SIRtotals.cpp -o $@

$(BINDIR)transportation.o: $(SRCDIR)transportation.cpp $(INCDIR)transportation.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)transportation.cpp -o $@

$(BINDIR)business.o: $(SRCDIR)business.cpp $(INCDIR)business.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)business.cpp -o $@

$(BINDIR)geographicalrisk.o: $(SRCDIR)geographicalrisk.cpp $(INCDIR)geographicalrisk.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)geographicalrisk.cpp -o $@

$(BINDIR)hospital.o: $(SRCDIR)hospital.cpp $(INCDIR)hospital.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)hospital.cpp -o $@

$(BINDIR)isolationcompartment.o: $(SRCDIR)isolationcompartment.cpp $(INCDIR)isolationcompartment.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)isolationcompartment.cpp -o $@

run:
	$(BINDIR)abmSim

memtest:
	valgrind --leak-check=full $(BINDIR)abmSim

clean:
	rm $(OBJECTS) $(BINDIR)abmSim