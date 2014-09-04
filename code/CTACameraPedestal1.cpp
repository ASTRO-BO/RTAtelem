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


#define RBLOCK_PEDLOW_PIXEL 0
#define RBLOCK_PEDHIGH_PIXEL 1
#define RBLOCK_SUMWIND_NSUM 2
#define RBLOCK_TZERO_PIXEL 3
#define RBLOCK_PEDVAR_NSUM 0

RTATelem::CTACameraPedestal1::CTACameraPedestal1(Packet* packet)
	: CTACameraPedestal(packet) {
	_type = CTA_CAMERA_PEDESTAL_1;
	header.setType(2);
}

PacketLib::ByteStreamPtr RTATelem::CTACameraPedestal1::getInputPacketData() {
	return RTATelem::CTAPacket::getInputPacketData();
}

void RTATelem::CTACameraPedestal1::setPedestalRun(word pedestalRun) {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	sdf->setFieldValue("pedestalRun", pedestalRun);
}

word RTATelem::CTACameraPedestal1::getPedestalRun() {
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	return sdf->getFieldValue("pedestalRun");
}

void RTATelem::CTACameraPedestal1::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setFieldValue(2, telescopeID);
}

word RTATelem::CTACameraPedestal1::getTelescopeId() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    return sdf->getFieldValue(2);
}


void RTATelem::CTACameraPedestal1::setNumberOfCalibrationPixels(word number) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setNumberOfBlocks(number, RBLOCK_PEDLOW_PIXEL);
    sdf->setNumberOfBlocks(number, RBLOCK_PEDHIGH_PIXEL);
    //sdf->setNumberOfBlocks(number, RBLOCK_PEDVARLOW_PIXEL); da rimuovere
    //sdf->setNumberOfBlocks(number, RBLOCK_PEDVARHIGH_PIXEL); da rimuovere
    sdf->setNumberOfBlocks(number, RBLOCK_TZERO_PIXEL);
}

word RTATelem::CTACameraPedestal1::getNumberOfCalibrationPixels() {
    /// Get a pointer to the source data field
    //SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    //return sdf->getNumberOfBlocks();
	/// alternative solution (faster)
	ByteStreamPtr fixedSdf = _packet->getBSSourceDataFieldsFixedPart();
	word* part = (word*) fixedSdf->stream;
	return part[4]; //number of pixel M
}

void RTATelem::CTACameraPedestal1::setNumberSummingWindows(word pixelIndex, word number) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixellow = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDLOW_PIXEL);
    SDFBlock* pixelhigh = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDHIGH_PIXEL);
    pixellow->setNumberOfBlocks(number, RBLOCK_PEDVAR_NSUM);
    pixelhigh->setNumberOfBlocks(number, RBLOCK_PEDVAR_NSUM);
    sdf->setNumberOfBlocks(number, RBLOCK_SUMWIND_NSUM);

}

word RTATelem::CTACameraPedestal1::getNumberSummingWindows(word pixelIndex) {
    /// Get a pointer to the source data field
	ByteStreamPtr fixedSdf = _packet->getBSSourceDataFieldsFixedPart();
	word* part = (word*) fixedSdf->stream;
	return part[3]; //number of pixel M
}


void RTATelem::CTACameraPedestal1::setPedestalHighValue(word pixelIndex, float pedHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDHIGH_PIXEL);
    pixel->setFieldValue_32f(0, pedHigh);
}

float RTATelem::CTACameraPedestal1::getPedestalHighValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDHIGH_PIXEL);
	float value = pixel->getFieldValue_32f(0);
    return value;       
}

void RTATelem::CTACameraPedestal1::setPedestalLowValue(word pixelIndex, float pedLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDLOW_PIXEL);
    pixel->setFieldValue_32f(0, pedLow);
}

float RTATelem::CTACameraPedestal1::getPedestalLowValue(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDLOW_PIXEL);
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


void RTATelem::CTACameraPedestal1::setPedVarHigh(word pixelIndex, word sumWindIndex, float pedvarHigh) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDHIGH_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_PEDVAR_NSUM);
    sumWindow->setFieldValue_32f(0, pedvarHigh);
}


float RTATelem::CTACameraPedestal1::getPedVarHigh(word pixelIndex, word sumWindIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDHIGH_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_PEDVAR_NSUM);
	float value = 0;
	if(sumWindow != 0)
		value = sumWindow->getFieldValue_32f(0);
	if(sumWindow == 0)
		value = pixel->getFieldValue_32f(sumWindIndex);
    return value;
}

void RTATelem::CTACameraPedestal1::setPedVarLow(word pixelIndex, word sumWindIndex, float pedvarLow) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDLOW_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_PEDVAR_NSUM);
    sumWindow->setFieldValue_32f(0, pedvarLow);
}


float RTATelem::CTACameraPedestal1::getPedVarLow(word pixelIndex, word sumWindIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PEDLOW_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sumWindow = (SDFBlock*) pixel->getBlock(sumWindIndex, RBLOCK_PEDVAR_NSUM);
	word value = 0;
	if(sumWindow != 0)
		value = sumWindow->getFieldValue_32f(0);
	if(sumWindow == 0)
		value = pixel->getFieldValue_32f(sumWindIndex);
    return value;
}

void RTATelem::CTACameraPedestal1::setSumWindows(word sumWindIndex, word sumWind) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* wind= (SDFBlock*) sdf->getBlock(sumWindIndex, RBLOCK_SUMWIND_NSUM);
    wind->setFieldValue(0, sumWind);
}


word RTATelem::CTACameraPedestal1::getSumWindows(word sumWindIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* wind = (SDFBlock*) sdf->getBlock(sumWindIndex, RBLOCK_SUMWIND_NSUM);
	word value = 0;
	if(wind != 0)
		value = wind->getFieldValue(0);
	if(wind == 0)
		value = wind->getFieldValue(sumWindIndex);
    return value;       
}


void RTATelem::CTACameraPedestal1::setTimeZero(word pixelIndex, float tzero) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_TZERO_PIXEL);
    pixel->setFieldValue_32f(0, tzero);
}

float RTATelem::CTACameraPedestal1::getTimeZero(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_TZERO_PIXEL);
	float value = 0;
	if(pixel != 0)
		value = pixel->getFieldValue_32f(0);
	if(pixel == 0)
		value = pixel->getFieldValue_32f(pixelIndex);
    return value;       
}
