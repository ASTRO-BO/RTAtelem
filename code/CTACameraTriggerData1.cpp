/***************************************************************************
                          CTACameraTriggerData1.cpp  -  description
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


#include "CTACameraTriggerData1.h"
#include <packet/OutputFile.h>
#include <packet/InputFile.h>
#include <packet/PacketDataField.h>
#include <packet/SDFRBlock.h>
#include <packet/OutputPacketStream.h>

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define RBLOCK_PIXELID 1
#define RBLOCK_SAMPLE 0

RTATelem::CTACameraTriggerData1::CTACameraTriggerData1(string packetConfig, string tmInputFileName, string tmOutputFileName) : CTACamera(packetConfig, tmInputFileName, tmOutputFileName) {

}

RTATelem::CTACameraTriggerData1::CTACameraTriggerData1(string packetConfig) : CTACamera(packetConfig) {


}


void RTATelem::CTACameraTriggerData1::writePacket() {
    
    header->setType(1);
    RTATelem::CTAPacket::writePacket();
}

void RTATelem::CTACameraTriggerData1::setTelescopeId(word telescopeID) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(2, telescopeID);
}

word RTATelem::CTACameraTriggerData1::getTelescopeId() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getFieldValue(2);
}


RTATelem::CTACameraTriggerData1::~CTACameraTriggerData1() {

}

void RTATelem::CTACameraTriggerData1::setNumberOfTriggeredTelescopes(byte number) {
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue(3, (word) number);
}

byte RTATelem::CTACameraTriggerData1::getNumberOfTriggeredTelescopes() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return (byte) sdf->getFieldValue(3);
}

void RTATelem::CTACameraTriggerData1::setIndexOfCurrentTriggeredTelescope(byte telescopeIndex) {
	 SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	 sdf->setFieldValue(4, (word) telescopeIndex);
}

byte RTATelem::CTACameraTriggerData1::getIndexOfCurrentTriggeredTelescope() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	return (byte) sdf->getFieldValue(4);
}



void RTATelem::CTACameraTriggerData1::setEventNumber(dword event) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setFieldValue_4_14(0, event);
}


dword RTATelem::CTACameraTriggerData1::getEventNumber() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getFieldValue_4_14(0);
}

void RTATelem::CTACameraTriggerData1::setNumberOfSamples(word pixelIndex, word number) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void RTATelem::CTACameraTriggerData1::setSampleValue(word pixelIndex, word sampleIndex, word FADC) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
    sample->setFieldValue(0, FADC);
}


word RTATelem::CTACameraTriggerData1::getPixelId(word pixelIndex) {
    /// Get a pointer to the source data field

	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXELID);
    return pixel->getFieldValue(0);

}


void RTATelem::CTACameraTriggerData1::setPixelId(word pixelIndex, word pixelID) {
    /// Get a pointer to the source data field

    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXELID);
    pixel->setFieldValue(0, pixelID);

}


ByteStreamPtr RTATelem::CTACameraTriggerData1::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    ByteStreamPtr p = pixel->getByteStream();
	p->swapWordForIntel();
	return p;
}

ByteStreamPtr RTATelem::CTACameraTriggerData1::getCameraDataSlow() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	int fixedpartdim = sdf->getFixedPart()->getDimension();
	
	ByteStreamPtr sdfbs = sdf->getByteStream();

	ByteStreamPtr camera = ByteStreamPtr(new ByteStream(sdfbs, fixedpartdim));

	/*ByteStreamPtr fixed = sdf->getFixedPart();
	int fixedpartdim = fixed->getDimension();
	int sdfdim = sdf->getDimension();
    
	sdfbs->swapWordForIntel();
	
	 */
	//ByteStreamPtr camera = sdf->getVariablePart(); //TODO NON FUNZIONA!!!!!!!
	camera->swapWordForIntel();
	return camera;
}

word RTATelem::CTACameraTriggerData1::getNumberOfSamples(word pixelIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    word nsamples =  pixel->getNumberOfRealDataBlock();
	if(nsamples == 0)
		nsamples = sdf->getFieldValue(6);
	return nsamples;
}

word RTATelem::CTACameraTriggerData1::getSampleValue(word pixelIndex, word sampleIndex) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
	word value = 0;
	if(sample != 0)
		value = sample->getFieldValue(0);
	if(sample == 0)
		value = pixel->getFieldValue(sampleIndex);
    return value;
}

void RTATelem::CTACameraTriggerData1::setNumberOfPixelsID(word number) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXELID);
}

word RTATelem::CTACameraTriggerData1::getNumberOfPixelsID() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getNumberOfRealDataBlock(RBLOCK_PIXELID);
}

