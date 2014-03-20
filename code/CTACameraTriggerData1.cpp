/***************************************************************************
    begin                : TODO
    copyright            : (C) 2014 Andrea Bulgarelli, Andrea Zoli
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

#include "CTACameraTriggerData1.h"

namespace RTATelem {

CTACameraTriggerData1::CTACameraTriggerData1(Packet* packet)
 : CTACameraTriggerData(packet) {
	_type = CTA_CAMERA_TRIGGERDATA_1;
	if(header)
		header->setType(1);
}

PacketLib::ByteStreamPtr CTACameraTriggerData1::getInputPacketData() {
	return RTATelem::CTAPacket::getInputPacketData();
}

void CTACameraTriggerData1::setNumberOfPixelsID(word number) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXELID);
}

word CTACameraTriggerData1::getNumberOfPixelsID() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    return sdf->getNumberOfRealDataBlock(RBLOCK_PIXELID);
}

ByteStreamPtr CTACameraTriggerData1::getPixelData(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    ByteStreamPtr p = pixel->getByteStream();
	p->swapWordForIntel();
	return p;
}

ByteStreamPtr CTACameraTriggerData1::getCameraDataSlow() {
    /// Get a pointer to the source data field
	/*
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	int fixedpartdim = sdf->getFixedPart()->size();
	
	ByteStreamPtr sdfbs = sdf->getByteStream();

	ByteStreamPtr camera = ByteStreamPtr(new ByteStream(sdfbs, fixedpartdim));
	*/
	
	return _packet->getBSSourceDataFieldsVariablePart();
	/*ByteStreamPtr fixed = sdf->getFixedPart();
	int fixedpartdim = fixed->size();
	int sdfdim = sdf->size();
    
	sdfbs->swapWordForIntel();
	
	 */
	//ByteStreamPtr camera = sdf->getVariablePart(); //TODO NON FUNZIONA!!!!!!!
	//camera->swapWordForIntel();
	//return camera;
}

word CTACameraTriggerData1::getNumberOfSamples(word pixelIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    word nsamples =  pixel->getNumberOfRealDataBlock();
	if(nsamples == 0)
		nsamples = sdf->getFieldValue(6);
	return nsamples;
}

word CTACameraTriggerData1::getSampleValue(word pixelIndex, word sampleIndex) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    SDFBlock* pixel = (SDFBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
    /// VARIABLE FORMAT
    SDFBlock* sample = (SDFBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
	word value = 0;
	if(sample != 0)
		value = sample->getFieldValue(0);
	if(sample == 0)
		value = pixel->getFieldValue(sampleIndex);
    return value;
}

}
