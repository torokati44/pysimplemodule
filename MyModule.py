import pyomnetpp

class MyModule(pyomnetpp.ModuleBase):
    def initialize(self):
        print("initialize()")
        
    def finish(self):
        print("finish()")
    
    def handleMessage(self, msg):
        self.send(msg)



"""
class Bar(cpp_module.Foo):
    def __init__(self):
        pass

    def foo(self):
        return "HohoHO!"

    def bar(self, x):
        return x/3.0


import flask

class Boo(cpp_module.Foo):
    def __init__(self):
        pass

    def foo(self):
        return str(dir(flask))

    def bar(self, x):
        return x/3.0
"""