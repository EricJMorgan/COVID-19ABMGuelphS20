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
    void incubationPeriodSetter(Simulation* sim, int val);
    void timeIncubHospitalSetter(Simulation* sim, int val);
    void timeHospitalICUSetter(Simulation* sim, int val);
    void timeICUDeathSetter(Simulation* sim, int val);
    void timeRecoveryNoHospitalSetter(Simulation* sim, int val);
    void recoveryPeriodHospitalSetter(Simulation* sim, int val);
    void timeRecoveryICUSetter(Simulation* sim, int val);
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

    def setSocialDistanceServerity
        lib.socialDistanceServeritySetter(self.obj, val)

    def setmaskCompliance
        lib.maskComplianceSetter(self.obj, val)

    def setHygieneMaintainence
        lib.hygieneMaintainenceSetter(self.obj, val)

    def setGenStoreRisk
        lib.genStoreRiskSetter(self.obj, val)

    def setTransportRisk
        lib.transportRiskSetter(self.obj, val)

    def setSchoolRisk
        lib.schoolRiskSetter(self.obj, val)

    def setParkRisk
        lib.parkRiskSetter(self.obj, val)

    def setEntertainmentRisk
        lib.entertainmentRiskSetter(self.obj, val)

    def setHealthPlaceRisk
        lib.healthPlaceRiskSetter(self.obj, val)

    def setPlaceOfWorshipRisk
        lib.placeOfWorshipRiskSetter(self.obj, val)

    def setResidentialRisk
        lib.residentialRiskSetter(self.obj, val)

    def setIncubationPeriod
        lib.incubationPeriodSetter(self.obj, int val)

    def setTimeIncubHospital
        lib.timeIncubHospitalSetter(self.obj, int val)

    def setTimeHospitalICU
        lib.timeHospitalICUSetter(self.obj, int val)

    def setTimeICUDeath
        lib.timeICUDeathSetter(self.obj, int val)

    def setTimeRecoveryNoHospital
        lib.timeRecoveryNoHospitalSetter(self.obj, val)

    def setRecoveryPeriodHospital
        lib.recoveryPeriodHospitalSetter(self.obj, val)
        
    def setTimeRecoveryICU
        lib.timeRecoveryICUSetter(self.obj, val)
    
    

sim = Simulation()
sim.timeStep()