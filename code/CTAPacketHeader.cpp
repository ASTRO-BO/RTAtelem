#include "CTAPacketHeader.h"
#include <packet/ByteStream.h>
#include <packet/Output.h>
#include <packet/Input.h>
#include <packet/Packet.h>

RTATelem::CTAPacketHeader::CTAPacketHeader(Packet* packet)
	: _packet(packet) {

}

void RTATelem::CTAPacketHeader::setAPID(word apid) {
    _packet->getPacketHeader()->setFieldValue(3, apid);
}

word RTATelem::CTAPacketHeader::getAPID() {
    return _packet->getPacketHeader()->getFieldValue(3);
}


void RTATelem::CTAPacketHeader::setSubType(byte subtype) {
	_packet->getPacketHeader()->setFieldValue(10, subtype);
}


word RTATelem::CTAPacketHeader::getSubType() {
	return _packet->getPacketHeader()->getFieldValue(10);
}

void RTATelem::CTAPacketHeader::setType(byte type) {
	_packet->getPacketHeader()->setFieldValue(9, type);
}


word RTATelem::CTAPacketHeader::getType() {
	return _packet->getPacketHeader()->getFieldValue(9);
}


void RTATelem::CTAPacketHeader::setSSC(word counter) {
    _packet->getPacketHeader()->setFieldValue(5, counter);
}

word RTATelem::CTAPacketHeader::getSSC() {
    return _packet->getPacketHeader()->getFieldValue(5);
}

void RTATelem::CTAPacketHeader::setMetadata(word arrayID, word runNumberID) {
    _packet->getPacketDataFieldHeader()->setFieldValue(4, arrayID);
    _packet->getPacketDataFieldHeader()->setFieldValue(5, runNumberID);
    //_packet->getPacketDataFieldHeader()->setFieldValue_4_14(5, eventNumberID);
}

void RTATelem::CTAPacketHeader::getMetadata(word &arrayID, word &runNumberID) {
    arrayID = _packet->getPacketDataFieldHeader()->getFieldValue(4);
    runNumberID = _packet->getPacketDataFieldHeader()->getFieldValue(5);
    //eventNumberID = _packet->getPacketDataFieldHeader()->getFieldValue_4_14(5);
}

void RTATelem::CTAPacketHeader::setTime(signed long time) {
    _packet->getPacketDataFieldHeader()->setFieldValue_4_14(0, time);
}


signed long RTATelem::CTAPacketHeader::getTime() {
    return _packet->getPacketDataFieldHeader()->getFieldValue_4_14(0);
}





