# move this stuff and delte the file once finished

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
    int hospitalTotal(Simulation* sim);
    int hospitalCurrent(Simulation* sim);
    int ICUtotal(Simulation* sim);
    int ICUCurrent(Simulation* sim);
    void socialDistanceServerity(Simulation* sim, int val);
    void maskCompliance(Simulation* sim, double val);
    void hygieneMaintainence(Simulation* sim, double val);
    void genStoreRisk(Simulation* sim, double val);
    void transportRisk(Simulation* sim, double val);
    void schoolRisk(Simulation* sim, double val);
    void parkRisk(Simulation* sim, double val);
    void entertainmentRisk(Simulation* sim, double val);
    void healthPlaceRisk(Simulation* sim, double val);
    void placeOfWorshipRisk(Simulation* sim, double val);
    void residentialRisk(Simulation* sim, double val);
    void incubationPeriod(Simulation* sim, int val);
    void timeIncubHospital(Simulation* sim, int val);
    void timeHospitalICU(Simulation* sim, int val);
    void timeICUDeath(Simulation* sim, int val);
    void timeRecoveryNoHospital(Simulation* sim, int val);
    void recoveryPeriodHospital(Simulation* sim, int val);
    void timeRecoveryICU(Simulation* sim, int val);
''')

lib = ffi.dlopen('./libProject.so')

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
        
    def hospitalTotal(self):
        return lib.hospitalTotal(self.obj)

    def hospitalCurrent(self):
        return lib.hospitalCurrent(self.obj)
    
    def ICUtotal(self):
        return lib.ICUtotal(self.obj)

    def ICUCurrent(self):
        return lib.ICUCurrent(self.obj)

sim = Simulation()
sim.timeStep()