/***************************************************************************
                          CTAPedestal.cpp  -  description
                             -------------------
    copyright            : (C) 2013 Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/


#include "CTAPedestal.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketDataField.h"
#include "SDFRBlock.h"
#include "Packet.h"

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0


void RTATelem::CTAPedestal::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(0, telescopeID);
}

word RTATelem::CTAPedestal::getTelescopeId() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getFieldValue(0);
}


RTATelem::CTAPedestal::CTAPedestal(string packetConfig, string tmInputFileName, string tmOutputFileName) :  CTAPacket(packetConfig, tmInputFileName, tmOutputFileName) {

}

RTATelem::CTAPedestal::~CTAPedestal() {

}


void RTATelem::CTAPedestal::setNumberOfPixels(word number) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
}


void RTATelem::CTAPedestal::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}


void RTATelem::CTAPedestal::setPedestalValue(word pixelIndex, word value) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(1, value);
}


word RTATelem::CTAPedestal::getNumberOfPixels() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getNumberOfRealDataBlock();
}


word RTATelem::CTAPedestal::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}


word RTATelem::CTAPedestal::getPedestalValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(1);
}

word RTATelem::CTAPedestal::getChannel() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return sdf->getFieldValue(1);
}

void RTATelem::CTAPedestal::setChannel(word channel) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	sdf->setFieldValue(1, channel);
}

word RTATelem::CTAPedestal::getPedestalRun() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return sdf->getFieldValue(2);
}

void RTATelem::CTAPedestal::setPedestalRun(word pede) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	sdf->setFieldValue(2, pede);
}
