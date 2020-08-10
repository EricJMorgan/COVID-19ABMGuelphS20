#
import random
from collections import deque

def start_X():
    X = deque()
    X.append(1)
    return X

def start_Y():
    Y = deque()
    Y.append(1)
    return Y

def get_X(value):
    return value + 1

def get_Y(value):
    return value + 0.1

def get_randomY(value):
    return value + (value * random.uniform(-0.1,0.1))


import cffi

ffi = cffi.FFI()
ffi.cdef('''
    typedef struct _Simulation Simulation;
    Simulation* Simulation_new();
    void simTimeStep(Simulation* sim);
    int infectedCurrent(Simulation* sim);
    int infectedTotal(Simulation* sim);
    int deceasedTotal(Simulation* sim);
    int recoveredTotal(Simulation* sim);
''')

lib = ffi.dlopen('../libProject.so')

class Simulation(object):
    def __init__(self):
        self.obj = lib.Simulation_new()

    def timeStep(self):
        lib.simTimeStep(self.obj)

    def infectedCurrent(self):
        return lib.infectedCurrent(self.obj)

    def infectedTotal(self):
        return lib.infectedTotal(self.obj)

    def deceasedTotal(self):
        return lib.deceasedTotal(self.obj)

    def recoveredTotal(self):
        return lib.recoveredTotal(self.obj)

sim = Simulation()
sim.timeStep()
print(sim.infectedCurrent())
print(sim.infectedTotal())
sim.timeStep()
print(sim.infectedCurrent())
sim.timeStep()
print(sim.infectedCurrent())
sim.timeStep()
print(sim.infectedCurrent())
sim.timeStep()
print(sim.infectedCurrent())
sim.timeStep()
print(sim.infectedCurrent())
sim.timeStep()
print(sim.infectedCurrent())
sim.timeStep()
print(sim.infectedCurrent())