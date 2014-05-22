#include "CTACamera.h"

#define RBLOCK_PIXEL 0

RTATelem::CTACamera::CTACamera(Packet* packet)
	: CTAPacket(packet), dimfixedUndefined(true) {
}

void RTATelem::CTACamera::setNumberOfPixels(word number) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    sdf->setNumberOfBlocks(number, RBLOCK_PIXEL);
}

word RTATelem::CTACamera::getNumberOfPixels() {
    /// Get a pointer to the source data field
    //SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
    //return sdf->getNumberOfBlocks();
	/// alternative solution (faster)
	ByteStreamPtr fixedSdf = _packet->getBSSourceDataFieldsFixedPart();
	word* part = (word*) fixedSdf->stream;
	return part[4]; //number of pixel M
}

/*
void RTATelem::CTACamera::setTelescopeId(word telescopeID) {
	cerr << "Implement RTATelem::CTACamera::setTelescopeId(word telescopeID)" << endl;
}


word RTATelem::CTACamera::getTelescopeId() {
	cerr << "Implement RTATelem::CTACamera::getTelescopeId()" << endl;
	return 0;
}

void RTATelem::CTACamera::setPixelId(word pixelIndex, word pixelID) {
	cerr << "Implement RTATelem::CTACamera::setPixelId(word pixelIndex, word pixelID)" << endl;
}

word RTATelem::CTACamera::getPixelId(word pixelIndex) {
	cerr << "Implement RTATelem::CTACamera::getPixelId(word pixelIndex)" << endl;
	return 0;
}
*/

dword RTATelem::CTACamera::sizeFixedPart() {
	//dword d1 = _packet->getPacketHeader()->size();
	//dword d2 = _packet->getPacketDataFieldHeader()->size();
	//SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	//dword d3 = sdf->sizeFixedPart();
	return _packet->sizeFixedPart();
}

ByteStreamPtr RTATelem::CTACamera::getCameraData(ByteStreamPtr rawPacket) {
	if(dimfixedUndefined) {
		dimfixed = sizeFixedPart();
		dimtail = _packet->sizeTail();
		dimfixedUndefined = false;
	}
	ByteStreamPtr camera = ByteStreamPtr(new ByteStream(rawPacket, dimfixed, rawPacket->size()-dimtail));
	camera->swapWordForIntel();
	return camera;
}
