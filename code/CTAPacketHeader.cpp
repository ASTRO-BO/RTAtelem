#include "CTAPacketHeader.h"
#include <packet/ByteStream.h>
#include <packet/Output.h>
#include <packet/Input.h>
#include <packet/Packet.h>

RTATelem::CTAPacketHeader::CTAPacketHeader(Packet* inputPacket, Packet* outputPacket) {
	this->inputPacket = inputPacket;
	this->outputPacket = outputPacket;
}

void RTATelem::CTAPacketHeader::setAPID(word apid) {
    outputPacket->getPacketHeader()->setFieldValue(3, apid);
}

word RTATelem::CTAPacketHeader::getAPID() {
    return inputPacket->getPacketHeader()->getFieldValue(3);
}


void RTATelem::CTAPacketHeader::setSubType(byte subtype) {
	outputPacket->getPacketHeader()->setFieldValue(10, subtype);
}


word RTATelem::CTAPacketHeader::getSubType() {
	return inputPacket->getPacketHeader()->getFieldValue(10);
}

void RTATelem::CTAPacketHeader::setType(byte type) {
	outputPacket->getPacketHeader()->setFieldValue(9, type);
}


word RTATelem::CTAPacketHeader::getType() {
	return inputPacket->getPacketHeader()->getFieldValue(9);
}


void RTATelem::CTAPacketHeader::setSSC(word counter) {
    outputPacket->getPacketHeader()->setFieldValue(5, counter);
}

word RTATelem::CTAPacketHeader::getSSC() {
    return inputPacket->getPacketHeader()->getFieldValue(5);
}

void RTATelem::CTAPacketHeader::setMetadata(word arrayID, word runNumberID) {
    outputPacket->getPacketDataFieldHeader()->setFieldValue(4, arrayID);
    outputPacket->getPacketDataFieldHeader()->setFieldValue(5, runNumberID);
    //outputPacket->getPacketDataFieldHeader()->setFieldValue_4_14(5, eventNumberID);
}

void RTATelem::CTAPacketHeader::getMetadata(word &arrayID, word &runNumberID) {
    arrayID = inputPacket->getPacketDataFieldHeader()->getFieldValue(4);
    runNumberID = inputPacket->getPacketDataFieldHeader()->getFieldValue(5);
    //eventNumberID = inputPacket->getPacketDataFieldHeader()->getFieldValue_4_14(5);
}

void RTATelem::CTAPacketHeader::setTime(signed long time) {
    outputPacket->getPacketDataFieldHeader()->setFieldValue_4_14(0, time);
}


signed long RTATelem::CTAPacketHeader::getTime() {
    return inputPacket->getPacketDataFieldHeader()->getFieldValue_4_14(0);
}





