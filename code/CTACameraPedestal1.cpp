/***************************************************************************
                          CTACameraPedestal1.cpp  -  description
                             -------------------
    copyright            : (C) 2014 Andrea Bulgarelli
                               2014 Valentina Fioretti
    email                : bulgarelli@iasfbo.inaf.it
                           fioretti@iasfbo.inaf.it
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
#include "CTACameraPedestal1.h"
#include <packet/OutputFile.h>
#include <packet/InputFile.h>
#include <packet/PacketDataField.h>
#include <packet/SDFBlock.h>
#include <packet/OutputPacketStream.h>

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define RBLOCK_NSUM 0

RTATelem::CTACameraPedestal1::CTACameraPedestal1(Packet* packet)
	: CTACameraPedestal(packet) {
	_type = CTA_CAMERA_PEDESTAL_0;
	header.setType(2);
}

PacketLib::ByteStreamPtr RTATelem::CTACameraPedestal1::getInputPacketData() {
	return RTATelem::CTAPacket::getInputPacketData();
}

void RTATelem::CTACameraPedestal1::setPedestalRun(word pede) {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	sdf->setFieldValue(0, pede);
}

word RTATelem::CTACameraPedestal1::getPedestalRun() {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	return sdf->getFieldValue(0);
}

void RTATelem::CTACameraPedestal1::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setFieldValue(1, telescopeID);
}

word RTATelem::CTACameraPedestal1::getTelescopeId() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    return sdf->getFieldValue(1);
}


/*
void RTATelem::CTACameraPedestal1::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}

word RTATelem::CTACameraPedestal1::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}
*/

void RTATelem::CTACameraPedestal1::setPedestalHighValue(word pixelIndex, float pedHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_5_1(0, pedHigh);
}

float RTATelem::CTACameraPedestal1::getPedestalHighValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_5_1(0);
}

void RTATelem::CTACameraPedestal1::setPedestalLowValue(word pixelIndex, float pedLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_5_1(2, pedLow);
}

float RTATelem::CTACameraPedestal1::getPedestalLowValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_5_1(2);
}


ByteStreamPtr RTATelem::CTACameraPedestal1::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    ByteStreamPtr p = pixel->getByteStream();
	p->swapWordForIntel();
	return p;
}

void RTATelem::CTACameraPedestal1::setNumberSummingWindows(word pixelIndex, word nsumWindows) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setNumberOfRealDataBlock(nsumWindows, RBLOCK_NSUM);
}

word RTATelem::CTACameraPedestal1::getNumberSummingWindows(word pixelIndex) {
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getNumberOfRealDataBlock();
}

void RTATelem::CTACameraPedestal1::setPedVarHigh(word pixelIndex, word sumWindIndex, float pedvarHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    sumWindow->setFieldValue_5_1(0, pedvarHigh);
}


float RTATelem::CTACameraPedestal1::getPedVarHigh(word pixelIndex, word sumWindIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    return sumWindow->getFieldValue_5_1(0);
}

void RTATelem::CTACameraPedestal1::setPedVarLow(word pixelIndex, word sumWindIndex, float pedvarLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    sumWindow->setFieldValue_5_1(2, pedvarLow);
}


float RTATelem::CTACameraPedestal1::getPedVarLow(word pixelIndex, word sumWindIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    return sumWindow->getFieldValue_5_1(2);
}
