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
    void socialDistanceServeritySetter(Simulation* sim, int val);
    void maskComplianceSetter(Simulation* sim, double val);
    void hygieneMaintainenceSetter(Simulation* sim, double val);
    void genStoreRiskSetter(Simulation* sim, double val);
    void transportRiskSetter(Simulation* sim, double val);
    void schoolRiskSetter(Simulation* sim, double val);
    void parkRiskSetter(Simulation* sim, double val);
    void entertainmentRiskSetter(Simulation* sim, double val);
    void healthPlaceRiskSetter(Simulation* sim, double val);
    void placeOfWorshipRiskSetter(Simulation* sim, double val);
    void residentialRiskSetter(Simulation* sim, double val);
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

    def setSocialDistanceServerity(self, val):
        lib.socialDistanceServeritySetter(self.obj, val)

    def setmaskCompliance(self, val):
        lib.maskComplianceSetter(self.obj, val)

    def setHygieneMaintainence(self, val):
        lib.hygieneMaintainenceSetter(self.obj, val)

    def setGenStoreRisk(self, val):
        lib.genStoreRiskSetter(self.obj, val)

    def setTransportRisk(self, val):
        lib.transportRiskSetter(self.obj, val)

    def setSchoolRisk(self, val):
        lib.schoolRiskSetter(self.obj, val)

    def setParkRisk(self, val):
        lib.parkRiskSetter(self.obj, val)

    def setEntertainmentRisk(self, val):
        lib.entertainmentRiskSetter(self.obj, val)

    def setHealthPlaceRisk(self, val):
        lib.healthPlaceRiskSetter(self.obj, val)

    def setPlaceOfWorshipRisk(self, val):
        lib.placeOfWorshipRiskSetter(self.obj, val)

    def setResidentialRisk(self, val):
        lib.residentialRiskSetter(self.obj, val)
sim = Simulation()

#set everything
sim.setSocialDistanceServerity(9)
sim.setmaskCompliance(0.5)
sim.setHygieneMaintainence(0.5)

sim.setGenStoreRisk(0.6)
sim.setTransportRisk(0.7)
sim.setSchoolRisk(0.8)
sim.setParkRisk(0.4)
sim.setEntertainmentRisk(0.7)
sim.setHealthPlaceRisk(0.8)
sim.setPlaceOfWorshipRisk(0.7)
sim.setResidentialRisk(0.5)
#loop sim timestep

sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
sim.timeStep()
