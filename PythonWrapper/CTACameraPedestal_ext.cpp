/***************************************************************************
 CTACameraPedestal_ext.cpp  -  description
 -------------------
 copyright            : (C) 2014 Valentina Fioretti
 email                : fioretti@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>
#include <CTACameraPedestal.cpp>
#include <CTACamera.cpp>
#include <CTAPacket.cpp>
#include <CTAPacketHeader.cpp>


using namespace boost::python;

class DummyCTA{};

BOOST_PYTHON_MODULE(CTACameraPedestal_ext)
{
         // Change the current scope 
         scope RTATelem
              = class_<DummyCTA>("RTATelem")
              ;

         class_<RTATelem::CTAPacketHeader>("CTAPacketHeader", no_init)
              .def("setSSC", &RTATelem::CTAPacketHeader::setSSC)
              //.def("getSSC", &RTATelem::CTAPacketHeader::getSSC)
              .def("setAPID", &RTATelem::CTAPacketHeader::setAPID)
              //.def("getAPID", &RTATelem::CTAPacketHeader::getAPID)
              .def("setMetadata", &RTATelem::CTAPacketHeader::setMetadata)
              //.def("getMetadata", &RTATelem::CTAPacketHeader::getMetadata)
              .def("setTime", &RTATelem::CTAPacketHeader::setTime)
              //.def("getTime", &RTATelem::CTAPacketHeader::getTime)
              ;

         class_<RTATelem::CTAPacket>("CTAPacket", no_init)
              .add_property("header",make_getter(&RTATelem::CTAPacket::header, return_value_policy<reference_existing_object>()),make_setter(&RTATelem::CTAPacket::header,return_value_policy<reference_existing_object>()))
              .def("writePacket", &RTATelem::CTAPacket::writePacket)
              //.def("readPacket", &CTAPacket_readPacket, (boost::python::arg("self")), "Get buffer")
              .def("readPacketPy", &RTATelem::CTAPacket::readPacketPy)
              .def("printPacket_output", &RTATelem::CTAPacket::printPacket_output)
              //.def("printPacket_input", &RTATelem::CTAPacket::printPacket_input)
              ; 
              
         class_<RTATelem::CTACamera, bases<RTATelem::CTAPacket> >("CTACamera", no_init)
              .def("setNumberOfPixels", &RTATelem::CTACamera::setNumberOfPixels)
              //.def("getNumberOfPixels", &RTATelem::CTACamera::getNumberOfPixels)
              ;               

         // Define a class A in the current scope, a
         class_<RTATelem::CTACameraPedestal, bases<RTATelem::CTACamera> >("CTACameraPedestal", init<std::string>())
              .def(init<std::string, std::string, std::string>())
              .def("setPedestalRun", &RTATelem::CTACameraPedestal::setPedestalRun)
              //.def("getPedestalRun", &RTATelem::CTACameraPedestal::getPedestalRun)
              .def("setTelescopeId", &RTATelem::CTACameraPedestal::setTelescopeId)
              //.def("getTelescopeId", &RTATelem::CTACameraPedestal::getTelescopeId)
              .def("setPixelId", &RTATelem::CTACameraPedestal::setPixelId)
              //.def("getPixelId", &RTATelem::CTACameraPedestal::getPixelId)
              .def("setPedestalHighValue", &RTATelem::CTACameraPedestal::setPedestalHighValue)
              //.def("getPedestalHighValue", &RTATelem::CTACameraPedestal::getPedestalHighValue)
              .def("setPedestalLowValue", &RTATelem::CTACameraPedestal::setPedestalLowValue)
              //.def("getPedestalLowValue", &RTATelem::CTACameraPedestal::getPedestalLowValue)

              ;

}

