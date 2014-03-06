/***************************************************************************
    begin                : TODO
    copyright            : (C) 2013-2014 Andrea Bulgarelli, Andrea Zoli
    email                : bulgarelli@iasfbo.inaf.it, zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#include "CTACameraTriggerData.h"

namespace RTATelem {

CTACameraTriggerData::CTACameraTriggerData(string packetConfig, string tmInputFileName, string tmOutputFileName) : CTACamera(packetConfig, tmInputFileName, tmOutputFileName) {

}

CTACameraTriggerData::CTACameraTriggerData(string packetConfig) : CTACamera(packetConfig) {

}

word RTATelem::CTACameraTriggerData::getTelescopeId() {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return sdf->getFieldValue(2);
}

void CTACameraTriggerData::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(2, telescopeID);
}

void CTACameraTriggerData::setNumberOfTriggeredTelescopes(byte number) {
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(3, (word) number);
}

byte CTACameraTriggerData::getNumberOfTriggeredTelescopes() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return (byte) sdf->getFieldValue(3);
}

void CTACameraTriggerData::setIndexOfCurrentTriggeredTelescope(byte telescopeIndex) {
	 SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	 sdf->setFieldValue(4, (word) telescopeIndex);
}

byte CTACameraTriggerData::getIndexOfCurrentTriggeredTelescope() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return (byte) sdf->getFieldValue(4);
}

void CTACameraTriggerData::setEventNumber(dword event) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue_4_14(0, event);
}

dword CTACameraTriggerData::getEventNumber() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getFieldValue_4_14(0);
}

void CTACameraTriggerData::setNumberOfSamples(word pixelIndex, word number) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void CTACameraTriggerData::setSampleValue(word pixelIndex, word sampleIndex, word FADC) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
    sample->setFieldValue(0, FADC);
}

void CTACameraTriggerData::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}

word CTACameraTriggerData::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}

}
