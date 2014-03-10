#include "CTACamera.h"

#define RBLOCK_PIXEL 0

RTATelem::CTACamera::CTACamera(string packetConfig, string tmInputFileName, string tmOutputFileName) : CTAPacket(packetConfig, tmInputFileName, tmOutputFileName) {
	dimfixed = -1;
}

RTATelem::CTACamera::CTACamera(string packetConfig) : CTAPacket(packetConfig) {
	dimfixed = -1;

}


RTATelem::CTACamera::~CTACamera() {
}

void RTATelem::CTACamera::setNumberOfPixels(word number) {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
    sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
}

word RTATelem::CTACamera::getNumberOfPixels() {
    /// Get a pointer to the source data field
    SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
    return sdf->getNumberOfRealDataBlock();
}

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

dword RTATelem::CTACamera::sizeFixedPart() {
	//dword d1 = inputPacket->getPacketHeader()->size();
	//dword d2 = inputPacket->getPacketDataFieldHeader()->size();
	//SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
	//dword d3 = sdf->sizeFixedPart();
	return inputPacket->sizeFixedPart();
}

ByteStreamPtr RTATelem::CTACamera::getCameraData(ByteStreamPtr rawPacket) {
	if(dimfixed == -1) {
		dimfixed = sizeFixedPart();
		dimtail = inputPacket->sizeTail();
	}
	ByteStreamPtr camera = ByteStreamPtr(new ByteStream(rawPacket, dimfixed, rawPacket->size()-dimtail));
	camera->swapWordForIntel();
	return camera;
}