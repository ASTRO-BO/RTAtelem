/***************************************************************************
                          CTACameraPedestal0.cpp  -  description
                             -------------------
    copyright            : (C) 2013 Andrea Bulgarelli
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
#include "CTACameraPedestal0.h"
#include <packet/OutputFile.h>
#include <packet/InputFile.h>
#include <packet/PacketDataField.h>
#include <packet/SDFBlock.h>
#include <packet/OutputPacketStream.h>

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define RBLOCK_NSUM 0

RTATelem::CTACameraPedestal0::CTACameraPedestal0(Packet* packet)
	: CTACameraPedestal(packet) {
	_type = CTA_CAMERA_PEDESTAL_0;
}

void RTATelem::CTACameraPedestal0::setPedestalRun(word pede) {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	sdf->setFieldValue(0, pede);
}

word RTATelem::CTACameraPedestal0::getPedestalRun() {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	return sdf->getFieldValue(0);
}

void RTATelem::CTACameraPedestal0::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setFieldValue(1, telescopeID);
}

word RTATelem::CTACameraPedestal0::getTelescopeId() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    return sdf->getFieldValue(1);
}



void RTATelem::CTACameraPedestal0::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}

word RTATelem::CTACameraPedestal0::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}

void RTATelem::CTACameraPedestal0::setPedestalHighValue(word pixelIndex, float pedHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_32f(1, pedHigh);
}

float RTATelem::CTACameraPedestal0::getPedestalHighValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_32f(1);
}

void RTATelem::CTACameraPedestal0::setPedestalLowValue(word pixelIndex, float pedLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_32f(3, pedLow);
}

float RTATelem::CTACameraPedestal0::getPedestalLowValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_32f(3);
}


ByteStreamPtr RTATelem::CTACameraPedestal0::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getByteStream();
}

void RTATelem::CTACameraPedestal0::setNumberSummingWindows(word pixelIndex, word nsumWindows) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setNumberOfBlocks(nsumWindows, RBLOCK_NSUM);
}

word RTATelem::CTACameraPedestal0::getNumberSummingWindows(word pixelIndex) {
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getNumberOfBlocks();
}

void RTATelem::CTACameraPedestal0::setPedVarHigh(word pixelIndex, word sumWindIndex, float pedvarHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    sumWindow->setFieldValue_32f(0, pedvarHigh);
}


float RTATelem::CTACameraPedestal0::getPedVarHigh(word pixelIndex, word sumWindIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    return sumWindow->getFieldValue_32f(0);
}

void RTATelem::CTACameraPedestal0::setPedVarLow(word pixelIndex, word sumWindIndex, float pedvarLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    sumWindow->setFieldValue_32f(2, pedvarLow);
}


float RTATelem::CTACameraPedestal0::getPedVarLow(word pixelIndex, word sumWindIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_NSUM);
    return sumWindow->getFieldValue_32f(2);
}
