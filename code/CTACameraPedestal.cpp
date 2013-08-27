/***************************************************************************
                          CTACameraPedestal.cpp  -  description
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


#include "CTACameraPedestal.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketDataField.h"
#include "SDFRBlock.h"
#include "Packet.h"

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0


void RTATelem::CTACameraPedestal::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(0, telescopeID);
}

word RTATelem::CTACameraPedestal::getTelescopeId() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getFieldValue(0);
}


RTATelem::CTACameraPedestal::CTACameraPedestal(string packetConfig, string tmInputFileName, string tmOutputFileName) :  CTACamera(packetConfig, tmInputFileName, tmOutputFileName) {

}

RTATelem::CTACameraPedestal::~CTACameraPedestal() {

}




void RTATelem::CTACameraPedestal::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}


void RTATelem::CTACameraPedestal::setPedestalValue(word pixelIndex, word value) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(1, value);
}




word RTATelem::CTACameraPedestal::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}


word RTATelem::CTACameraPedestal::getPedestalValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(1);
}

word RTATelem::CTACameraPedestal::getChannel() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return sdf->getFieldValue(1);
}

void RTATelem::CTACameraPedestal::setChannel(word channel) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	sdf->setFieldValue(1, channel);
}

word RTATelem::CTACameraPedestal::getPedestalRun() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return sdf->getFieldValue(2);
}

void RTATelem::CTACameraPedestal::setPedestalRun(word pede) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	sdf->setFieldValue(2, pede);
}
