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

#include "CTACameraTriggerData0.h"

namespace RTATelem {

CTACameraTriggerData0::CTACameraTriggerData0(const string& packetConfig, const string& tmInputFileName, const string& tmOutputFileName)
	: CTACameraTriggerData(packetConfig, tmInputFileName, tmOutputFileName) {

}

CTACameraTriggerData0::CTACameraTriggerData0(const string& packetConfig) : CTACameraTriggerData(packetConfig) {

}

CTACameraTriggerData0::~CTACameraTriggerData0() {

}

ByteStreamPtr CTACameraTriggerData0::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getByteStream();
}

word CTACameraTriggerData0::getNumberOfSamples(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getNumberOfRealDataBlock();
}

word CTACameraTriggerData0::getSampleValue(word pixelIndex, word sampleIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
    return sample->getFieldValue(0);
}

}