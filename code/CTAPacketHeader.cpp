#include "CTAPacketHeader.h"
#include "ByteStream.h"
#include "Output.h"
#include "Input.h"
#include "Packet.h"

RTATelem::CTAPacketHeader::CTAPacketHeader(Packet* inputPacket, Packet* outputPacket) {
	this->inputPacket = inputPacket;
	this->outputPacket = outputPacket;
}

void RTATelem::CTAPacketHeader::setAPID(word apid) {
    outputPacket->header->setFieldValue(3, apid);
}

word RTATelem::CTAPacketHeader::getAPID() {
    return inputPacket->header->getFieldValue(3);
}


void RTATelem::CTAPacketHeader::setSSC(word counter) {
    outputPacket->header->setFieldValue(5, counter);
}

word RTATelem::CTAPacketHeader::getSSC() {
    return inputPacket->header->getFieldValue(5);
}

void RTATelem::CTAPacketHeader::setMetadata(word arrayID, word runNumberID) {
    outputPacket->dataField->dataFieldHeader->setFieldValue(7, arrayID);
    outputPacket->dataField->dataFieldHeader->setFieldValue(8, runNumberID);
    //outputPacket->dataField->dataFieldHeader->setFieldValue_4_14(5, eventNumberID);
}

void RTATelem::CTAPacketHeader::getMetadata(word &arrayID, word &runNumberID) {
    arrayID = inputPacket->dataField->dataFieldHeader->getFieldValue(7);
    runNumberID = inputPacket->dataField->dataFieldHeader->getFieldValue(8);
    //eventNumberID = inputPacket->dataField->dataFieldHeader->getFieldValue_4_14(5);
}

void RTATelem::CTAPacketHeader::setTime(signed long time) {
    outputPacket->dataField->dataFieldHeader->setFieldValue_4_14(3, time);
}


signed long RTATelem::CTAPacketHeader::getTime() {
    return inputPacket->dataField->dataFieldHeader->getFieldValue_4_14(3);
}





