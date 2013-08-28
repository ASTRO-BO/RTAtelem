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
