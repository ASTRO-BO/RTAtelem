/***************************************************************************
                          CTACameraConv1.cpp  -  description
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


#include "CTACameraConv.h"
#include "CTACameraConv1.h"
#include <packet/OutputFile.h>
#include <packet/InputFile.h>
#include <packet/PacketDataField.h>
#include <packet/SDFBlock.h>
#include <packet/OutputPacketStream.h>


#define RBLOCK_CONVLOW_PIXEL 0
#define RBLOCK_CONVHIGH_PIXEL 1


RTATelem::CTACameraConv1::CTACameraConv1(Packet* packet)
	: CTACameraConv(packet) {
	_type = CTA_CAMERA_CONVERSION_1;
	header.setType(3);
}

PacketLib::ByteStreamPtr RTATelem::CTACameraConv1::getInputPacketData() {
	return RTATelem::CTAPacket::getInputPacketData();
}

void RTATelem::CTACameraConv1::setConversionRun(word conversionRun) {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	sdf->setFieldValue("conversionRun", conversionRun);
}

word RTATelem::CTACameraConv1::getConversionRun() {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	return sdf->getFieldValue("conversionRun");
}

void RTATelem::CTACameraConv1::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setFieldValue(2, telescopeID);
}

word RTATelem::CTACameraConv1::getTelescopeId() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    return sdf->getFieldValue(2);
}


void RTATelem::CTACameraConv1::setNumberOfCalibrationPixels(word number) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setNumberOfBlocks(number, RBLOCK_CONVLOW_PIXEL);
    sdf->setNumberOfBlocks(number, RBLOCK_CONVHIGH_PIXEL);
}

word RTATelem::CTACameraConv1::getNumberOfCalibrationPixels() {
    /// Get a pointer to the source data field
    //SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    //return sdf->getNumberOfBlocks();
	/// alternative solution (faster)
	ByteStreamPtr fixedSdf = _packet->getBSSourceDataFieldsFixedPart();
	word* part = (word*) fixedSdf->stream;
	return part[3]; //number of pixel M
}


void RTATelem::CTACameraConv1::setConversionHighValue(word pixelIndex, float convHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_CONVHIGH_PIXEL);
    pixel->setFieldValue_32f(0, convHigh);
}

float RTATelem::CTACameraConv1::getConversionHighValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_CONVHIGH_PIXEL);
	float value = pixel->getFieldValue_32f(0);
    return value;       
}

void RTATelem::CTACameraConv1::setConversionLowValue(word pixelIndex, float convLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_CONVLOW_PIXEL);
    pixel->setFieldValue_32f(0, convLow);
}

float RTATelem::CTACameraConv1::getConversionLowValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_CONVLOW_PIXEL);
	float value = pixel->getFieldValue_32f(0);
    return value;       
}

/*
ByteStreamPtr RTATelem::CTACameraPedestal1::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDHIGH_PIXEL);
    ByteStreamPtr p = pixel->getByteStream();
	p->swapWordForIntel();
	return p;
}*/