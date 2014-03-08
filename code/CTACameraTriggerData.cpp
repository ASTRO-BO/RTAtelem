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
	SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
	return sdf->getFieldValue(2);
}

void CTACameraTriggerData::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    sdf->setFieldValue(2, telescopeID);
}

void CTACameraTriggerData::setNumberOfTriggeredTelescopes(byte number) {
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    sdf->setFieldValue(3, (word) number);
}

byte CTACameraTriggerData::getNumberOfTriggeredTelescopes() {
	SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
	return (byte) sdf->getFieldValue(3);
}

void CTACameraTriggerData::setIndexOfCurrentTriggeredTelescope(byte telescopeIndex) {
	 SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
	 sdf->setFieldValue(4, (word) telescopeIndex);
}

byte CTACameraTriggerData::getIndexOfCurrentTriggeredTelescope() {
	SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
	return (byte) sdf->getFieldValue(4);
}

void CTACameraTriggerData::setEventNumber(dword event) {
	SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    sdf->setFieldValue_4_14(0, event);
}

dword CTACameraTriggerData::getEventNumber() {
	SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    return sdf->getFieldValue_4_14(0);
}

void CTACameraTriggerData::setNumberOfSamples(word pixelIndex, word number) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void CTACameraTriggerData::setSampleValue(word pixelIndex, word sampleIndex, word FADC) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sample = (SDFBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
    sample->setFieldValue(0, FADC);
}

void CTACameraTriggerData::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}

word CTACameraTriggerData::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}

}
