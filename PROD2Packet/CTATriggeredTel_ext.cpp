#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>
#include <CTATriggeredTelescope.cpp>

using namespace boost::python;

class DummyCTA{};

BOOST_PYTHON_MODULE(CTATriggeredTel_ext)
{
         // Change the current scope 
         scope RTATelem
             = class_<DummyCTA>("RTATelem")
             ;

         // Define a class A in the current scope, a
         class_<RTATelem::CTATriggeredTelescope>("CTATriggeredTelescope", init<std::string>())
              .def(init<std::string, std::string, std::string>())
              .def("setMetadata", &RTATelem::CTATriggeredTelescope::setMetadata)
              .def("setNumberOfTriggeredTelescopes", &RTATelem::CTATriggeredTelescope::setNumberOfTriggeredTelescopes)
              .def("setIndexOfCurrentTriggeredTelescopes", &RTATelem::CTATriggeredTelescope::setIndexOfCurrentTriggeredTelescopes)
              .def("setTelescopeId", &RTATelem::CTATriggeredTelescope::setTelescopeId)
              .def("setNumberOfPixels", &RTATelem::CTATriggeredTelescope::setNumberOfPixels)
              .def("setPixelId", &RTATelem::CTATriggeredTelescope::setPixelId)
              .def("setNumberOfSamples", &RTATelem::CTATriggeredTelescope::setNumberOfSamples)
              .def("setSampleValue", &RTATelem::CTATriggeredTelescope::setSampleValue)
              .def("writePacket", &RTATelem::CTATriggeredTelescope::writePacket)
              .def("printPacket_output", &RTATelem::CTATriggeredTelescope::printPacket_output)
              ;

}

