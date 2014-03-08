/***************************************************************************
                          CTACameraConv0.cpp  -  description
                             -------------------
    copyright            : (C) 2014 Valentina Fioretti
    email                : fioretti@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/


#include "CTACameraConv0.h"
#include <packet/OutputFile.h>
#include <packet/InputFile.h>
#include <packet/PacketDataField.h>
#include <packet/SDFBlock.h>
#include <packet/OutputPacketStream.h>

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0

RTATelem::CTACameraConv0::CTACameraConv0(string packetConfig, string tmInputFileName, string tmOutputFileName) : CTACamera(packetConfig, tmInputFileName, tmOutputFileName) {

}

RTATelem::CTACameraConv0::CTACameraConv0(string packetConfig) : CTACamera(packetConfig) {


}

RTATelem::CTACameraConv0::~CTACameraConv0() {

}

void RTATelem::CTACameraConv0::setConversionRun(word conv) {
	SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
	sdf->setFieldValue(0, conv);
}

word RTATelem::CTACameraConv0::getConversionRun() {
	SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
	return sdf->getFieldValue(0);
}

void RTATelem::CTACameraConv0::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    sdf->setFieldValue(1, telescopeID);
}

word RTATelem::CTACameraConv0::getTelescopeId() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    return sdf->getFieldValue(1);
}



void RTATelem::CTACameraConv0::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}

word RTATelem::CTACameraConv0::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}

void RTATelem::CTACameraConv0::setConversionHighValue(word pixelIndex, float convHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_5_1(1, convHigh);
}

float RTATelem::CTACameraConv0::getConversionHighValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_5_1(1);
}

void RTATelem::CTACameraConv0::setConversionLowValue(word pixelIndex, float convLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_5_1(3, convLow);
}

float RTATelem::CTACameraConv0::getConversionLowValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_5_1(3);
}

ByteStreamPtr RTATelem::CTACameraConv0::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getByteStream();
}
