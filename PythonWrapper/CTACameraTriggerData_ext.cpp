/***************************************************************************
 CTACameraTriggerData_ext.cpp  -  description
 -------------------
 copyright            : (C) 2013 Valentina Fioretti
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
#include <CTACameraTriggerData.cpp>
#include <CTACamera.cpp>
#include <CTAPacket.cpp>
#include <CTAPacketHeader.cpp>


using namespace boost::python;

class DummyCTA{};

BOOST_PYTHON_MODULE(CTACameraTriggerData_ext)
{
         // Change the current scope 
         scope RTATelem
              = class_<DummyCTA>("RTATelem")
              ;

         class_<RTATelem::CTAPacketHeader>("CTAPacketHeader", no_init)
              .def("setSSC", &RTATelem::CTAPacketHeader::setSSC)
              .def("getSSC", &RTATelem::CTAPacketHeader::getSSC)
              .def("setAPID", &RTATelem::CTAPacketHeader::setAPID)
              .def("getAPID", &RTATelem::CTAPacketHeader::getAPID)
              .def("setMetadata", &RTATelem::CTAPacketHeader::setMetadata)
              .def("getMetadata", &RTATelem::CTAPacketHeader::getMetadata)
              .def("setTime", &RTATelem::CTAPacketHeader::setTime)
              .def("getTime", &RTATelem::CTAPacketHeader::getTime)
              ;

         class_<RTATelem::CTAPacket>("CTAPacket", no_init)
              //.def(init<std::string, std::string, std::string>())
              .add_property("header",make_getter(&RTATelem::CTAPacket::header, return_value_policy<reference_existing_object>()),make_setter(&RTATelem::CTAPacket::header,return_value_policy<reference_existing_object>()))

              .def("writePacket", &RTATelem::CTAPacket::writePacket)
              .def("readPacketPy", &RTATelem::CTAPacket::readPacketPy)
              .def("printPacket_output", &RTATelem::CTAPacket::printPacket_output)
              //.def("printPacket_input", &RTATelem::CTAPacket::printPacket_input)
              ; 
              
         class_<RTATelem::CTACamera, bases<RTATelem::CTAPacket> >("CTACamera", no_init)
              //.def(init<std::string, std::string, std::string>())
              .def("setNumberOfPixels", &RTATelem::CTACamera::setNumberOfPixels)
              .def("getNumberOfPixels", &RTATelem::CTACamera::getNumberOfPixels)
              ;               
         
         // Define a class A in the current scope, a
         class_<RTATelem::CTACameraTriggerData, bases<RTATelem::CTACamera> >("CTACameraTriggerData", init<std::string>())
              .def(init<std::string, std::string, std::string>())
              .def("setTelescopeId", &RTATelem::CTACameraTriggerData::setTelescopeId)
              .def("getTelescopeId", &RTATelem::CTACameraTriggerData::getTelescopeId)
              .def("setEventNumber", &RTATelem::CTACameraTriggerData::setEventNumber)
              .def("getEventNumber", &RTATelem::CTACameraTriggerData::getEventNumber)
              .def("setNumberOfTriggeredTelescopes", &RTATelem::CTACameraTriggerData::setNumberOfTriggeredTelescopes)
              .def("getNumberOfTriggeredTelescopes", &RTATelem::CTACameraTriggerData::getNumberOfTriggeredTelescopes)
              .def("setIndexOfCurrentTriggeredTelescope", &RTATelem::CTACameraTriggerData::setIndexOfCurrentTriggeredTelescope)
              .def("getIndexOfCurrentTriggeredTelescope", &RTATelem::CTACameraTriggerData::getIndexOfCurrentTriggeredTelescope)
              .def("setPixelId", &RTATelem::CTACameraTriggerData::setPixelId)
              .def("getPixelId", &RTATelem::CTACameraTriggerData::getPixelId)
              .def("setNumberOfSamples", &RTATelem::CTACameraTriggerData::setNumberOfSamples)
              .def("getNumberOfSamples", &RTATelem::CTACameraTriggerData::getNumberOfSamples)
              .def("setSampleValue", &RTATelem::CTACameraTriggerData::setSampleValue)
              .def("getSampleValue", &RTATelem::CTACameraTriggerData::getSampleValue)
              ;

}

