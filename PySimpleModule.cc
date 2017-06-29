//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "PySimpleModule.h"

#include <string>
#include <iostream>

namespace py = pybind11;
using namespace py;


class ModuleBase {
    PySimpleModule *mod;
public:

    ModuleBase(PySimpleModule *mod) : mod(mod) {}

    void send(cMessage *msg, std::string gateName, int gateIndex = -1) {
        mod->send(msg, mod->gate(gateName.c_str(), gateIndex));
    }

    static void info(std::string msg) {
        EV_INFO << msg << std::endl;
    }
};


Define_Module(PySimpleModule);


int PySimpleModule::pyModuleCount = 0;

void PySimpleModule::initialize()
{
    if (pyModuleCount == 0)
        py::initialize_interpreter();

    ++pyModuleCount;

    std::string pythonModule = par("pythonModule").stringValue();
    std::string pythonClass = par("pythonClass").stringValue();

    if (pythonModule.empty())
        pythonModule = pythonClass;

    py::object implModule  = py::module::import(pythonModule.c_str());

    py::object moduleClass = implModule.attr(pythonClass.c_str());
    impl = new py::object(moduleClass(this));

    impl->attr("initialize")();


}

void PySimpleModule::finish()
{
    impl->attr("finish")();
    delete impl;
    impl = nullptr;

    --pyModuleCount;

    if (pyModuleCount == 0)
        py::finalize_interpreter();
}


void PySimpleModule::handleMessage(cMessage *msg)
{
    impl->attr("handleMessage")(msg);
}


PYBIND11_EMBEDDED_MODULE(pyomnetpp, m) {

    // global (static-ish) methods
    m
        .def("info", &ModuleBase::info)
        .def("simTime", &omnetpp::simTime)
        ;


    // Opaque type, just so a pointer to this can be passed through to the python object and back
    py::class_<PySimpleModule>(m, "PySimpleModule");

    // the module itself
    py::class_<ModuleBase>(m, "ModuleBase")
        .def(py::init<PySimpleModule*>())
        .def("send", &ModuleBase::send, "msg"_a, "gateName"_a, "gateIndex"_a = -1)
    ;

    py::class_<SimTime>(m, "SimTime")
            .def("__str__", (std::string (SimTime::*)() const) &SimTime::str)
            ;

    py::class_<cEvent>(m, "cEvent")
            .def_property_readonly("arrivalTime", &cEvent::getArrivalTime)
                ;

    py::class_<cMessage, cEvent>(m, "cMessage")
        .def(py::init<const char *>())
        .def_property("kind", &cMessage::getKind, &cMessage::setKind)
        .def("dup", &cMessage::dup, py::return_value_policy::reference)
            ;

}



#if 0

int maiaan() {

    auto py_module = py::module::import("py_module");
    auto locals = py::dict(**py_module.attr("__dict__"));

/*
    py::object module  = py::module::import("BarImpl");

    py::object Bar2 = module.attr("Bar");
    py::object bar = Bar2();

    std::cout << py::str(bar.attr("foo")()).cast<std::string>() << std::endl;



    py::object Boo = module.attr("Boo");
    py::object boo = Boo();

    std::cout << py::str(boo.attr("foo")()).cast<std::string>() << std::endl;
*/


    /*******
        try {

                py::exec(line, py::globals(), locals);
        }
        catch(const py::error_already_set& e)
        {
            std::cerr << "!!! " << e.what() << std::endl;

            //PyErr_Print();
            //std::cerr << std::endl;
        }
*****/
}

#endif

