from pyomnetpp import *

import pyomnetpp as pyo

class PyClassifier(ModuleBase):
    def initialize(self):
        info("classifier initialize()")
        info(str(dir(pyo)))
        
    def finish(self):
        info("classifier finish()")
    
    def handleMessage(self, msg):
        info("classifier handling " + str(msg.kind) + " arriving at time " + str(msg.arrivalTime) + " and now it's " + str(simTime()))
        clone = msg.dup()
        clone.kind = 3;
        self.send(msg, "out", msg.kind)
        self.send(clone, "out", 1 - msg.kind)
        
        #eh = cMessage("Eh!")
        
        #self.send(eh.dup(), "out", 1)
