/***************************************************************************
                          CTATriggeredTelescope.cpp  -  description
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


#include "CTATriggeredTelescope.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketDataField.h"
#include "SDFRBlock.h"
#include "OutputPacketStream.h"

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define RBLOCK_SAMPLE 0


void RTATelem::CTATriggeredTelescope::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(2, telescopeID);
}

word RTATelem::CTATriggeredTelescope::getTelescopeId() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getFieldValue(2);
}

RTATelem::CTATriggeredTelescope::CTATriggeredTelescope(string packetConfig, string tmInputFileName, string tmOutputFileName) : CTAPacket(packetConfig, tmInputFileName, tmOutputFileName) {

}

RTATelem::CTATriggeredTelescope::~CTATriggeredTelescope() {

}

void RTATelem::CTATriggeredTelescope::setNumberOfTriggeredTelescopes(byte number) {
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(3, (word) number);
}

byte RTATelem::CTATriggeredTelescope::getNumberOfTriggeredTelescopes() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return (byte) sdf->getFieldValue(3);
}

void RTATelem::CTATriggeredTelescope::setIndexOfCurrentTriggeredTelescopes(byte telescopeIndex) {
	 SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	 sdf->setFieldValue(4, (word) telescopeIndex);
}

byte RTATelem::CTATriggeredTelescope::getIndexOfCurrentTriggeredTelescopes() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return (byte) sdf->getFieldValue(4);
}

void RTATelem::CTATriggeredTelescope::setNumberOfPixels(word number) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
}

word RTATelem::CTATriggeredTelescope::getNumberOfPixels() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getNumberOfRealDataBlock();
}


void RTATelem::CTATriggeredTelescope::setEventNumber(dword event) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue_4_14(0, event);
}


dword RTATelem::CTATriggeredTelescope::getEventNumber() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getFieldValue_4_14(0);
}

void RTATelem::CTATriggeredTelescope::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}

void RTATelem::CTATriggeredTelescope::setNumberOfSamples(word pixelIndex, word number) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void RTATelem::CTATriggeredTelescope::setSampleValue(word pixelIndex, word sampleIndex, word FADC) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
    sample->setFieldValue(0, FADC);
}


word RTATelem::CTATriggeredTelescope::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}

word RTATelem::CTATriggeredTelescope::getNumberOfSamples(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getNumberOfRealDataBlock();
}

word RTATelem::CTATriggeredTelescope::getSampleValue(word pixelIndex, word sampleIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
    return sample->getFieldValue(0);
}
