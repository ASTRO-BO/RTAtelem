/***************************************************************************
                          CTACameraConv1.cpp  -  description
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


#include "CTACameraConv.h"
#include "CTACameraConv1.h"
#include <packet/OutputFile.h>
#include <packet/InputFile.h>
#include <packet/PacketDataField.h>
#include <packet/SDFBlock.h>
#include <packet/OutputPacketStream.h>

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0

RTATelem::CTACameraConv1::CTACameraConv1(Packet* packet)
	: CTACameraConv(packet) {
	_type = CTA_CAMERA_CONV_1;
	if(header)
		header->setType(3);
}

PacketLib::ByteStreamPtr RTATelem::CTACameraConv1::getInputPacketData() {
    return RTATelem::CTAPacket::getInputPacketData();
}

void RTATelem::CTACameraConv1::setConversionRun(word conv) {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	sdf->setFieldValue(0, conv);
}

word RTATelem::CTACameraConv1::getConversionRun() {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	return sdf->getFieldValue(0);
}

void RTATelem::CTACameraConv1::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setFieldValue(1, telescopeID);
}

word RTATelem::CTACameraConv1::getTelescopeId() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    return sdf->getFieldValue(1);
}

/*

void RTATelem::CTACameraConv1::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue(0, pixelID);
}

word RTATelem::CTACameraConv1::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue(0);
}
*/
void RTATelem::CTACameraConv1::setConversionHighValue(word pixelIndex, float convHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_5_1(0, convHigh);
}

float RTATelem::CTACameraConv1::getConversionHighValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_5_1(0);
}

void RTATelem::CTACameraConv1::setConversionLowValue(word pixelIndex, float convLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setFieldValue_5_1(2, convLow);
}

float RTATelem::CTACameraConv1::getConversionLowValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    return pixel->getFieldValue_5_1(2);
}

ByteStreamPtr RTATelem::CTACameraConv1::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    ByteStreamPtr p = pixel->getByteStream();
	p->swapWordForIntel();
	return p;
}
