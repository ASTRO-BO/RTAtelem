#include "CTACamera.h"

#define RBLOCK_PIXEL 0

RTATelem::CTACamera::CTACamera(string packetConfig, string tmInputFileName, string tmOutputFileName) : CTAPacket(packetConfig, tmInputFileName, tmOutputFileName) {

}

RTATelem::CTACamera::~CTACamera() {
}

void RTATelem::CTACamera::setNumberOfPixels(word number) {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
    sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
}

word RTATelem::CTACamera::getNumberOfPixels() {
    /// Get a pointer to the source data field
    SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
    return sdf->getNumberOfRealDataBlock();
}

void RTATelem::CTACamera::setTelescopeId(word telescopeID) {
	cerr << "Implement RTATelem::CTACamera::setTelescopeId(word telescopeID)" << endl;
}

word RTATelem::CTACamera::getTelescopeId() {
	cerr << "Implement RTATelem::CTACamera::getTelescopeId()" << endl;
}

void RTATelem::CTACamera::setPixelId(word pixelIndex, word pixelID) {
	cerr << "Implement RTATelem::CTACamera::setPixelId(word pixelIndex, word pixelID)" << endl;
}

word RTATelem::CTACamera::getPixelId(word pixelIndex) {
	cerr << "Implement RTATelem::CTACamera::getPixelId(word pixelIndex)" << endl;
}
