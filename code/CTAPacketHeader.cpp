#include "CTAPacketHeader.h"
#include <packet/ByteStream.h>
#include <packet/Output.h>
#include <packet/Input.h>
#include <packet/Packet.h>

RTATelem::CTAPacketHeader::CTAPacketHeader(Packet* packet)
	: _packet(packet) {

}

void RTATelem::CTAPacketHeader::setAPID(word apid) {
	if(_packet)
	    _packet->getPacketHeader()->setFieldValue(3, apid);
}

word RTATelem::CTAPacketHeader::getAPID() {
	if(!_packet)
		return -1;
    return _packet->getPacketHeader()->getFieldValue(3);
}


void RTATelem::CTAPacketHeader::setSubType(byte subtype) {
	if(_packet)
		_packet->getPacketHeader()->setFieldValue(10, subtype);
}


word RTATelem::CTAPacketHeader::getSubType() {
	if(!_packet)
		return -1;
	return _packet->getPacketHeader()->getFieldValue(10);
}

void RTATelem::CTAPacketHeader::setType(byte type) {
	if(_packet)
		_packet->getPacketHeader()->setFieldValue(9, type);
}


word RTATelem::CTAPacketHeader::getType() {
	if(!_packet)
		return -1;
	return _packet->getPacketHeader()->getFieldValue(9);
}


void RTATelem::CTAPacketHeader::setSSC(word counter) {
	if(_packet)
	    _packet->getPacketHeader()->setFieldValue(5, counter);
}

word RTATelem::CTAPacketHeader::getSSC() {
	if(!_packet)
		return -1;
    return _packet->getPacketHeader()->getFieldValue(5);
}

void RTATelem::CTAPacketHeader::setMetadata(word arrayID, word runNumberID) {
	if(_packet)
	{
	    _packet->getPacketDataFieldHeader()->setFieldValue(4, arrayID);
	    _packet->getPacketDataFieldHeader()->setFieldValue(5, runNumberID);
	    //_packet->getPacketDataFieldHeader()->setFieldValue_32ui(5, eventNumberID);
	}
}

void RTATelem::CTAPacketHeader::getMetadata(word &arrayID, word &runNumberID) {
	if(_packet)
	{
	    arrayID = _packet->getPacketDataFieldHeader()->getFieldValue(4);
	    runNumberID = _packet->getPacketDataFieldHeader()->getFieldValue(5);
	    //eventNumberID = _packet->getPacketDataFieldHeader()->getFieldValue_32ui(5);
	}
}

void RTATelem::CTAPacketHeader::setTime(signed long time) {
	if(_packet)
	    _packet->getPacketDataFieldHeader()->setFieldValue_32ui(0, time);
}


signed long RTATelem::CTAPacketHeader::getTime() {
	if(!_packet)
		return -1;
    return _packet->getPacketDataFieldHeader()->getFieldValue_32ui(0);
}
