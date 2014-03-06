/***************************************************************************
 CTAPacketBufferV.h  -  A FIFO buffer class for Packets
 -------------------
    copyright            : (C) 2013 Andrea Zoli
    email                : zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#include "CTAPacket.h"
#include "CTAPacketBufferV.h"

using namespace PacketLib;

namespace RTATelem
{

CTAPacketBufferV::CTAPacketBufferV(const string& packetConfig, const string& tmInputFile) : packet(packetConfig, tmInputFile, "")
{
	currentIndex = 0;
	currentIndexBS = 0;
}

CTAPacketBufferV::~CTAPacketBufferV()
{
}

void CTAPacketBufferV::load()
{
	ByteStreamPtr packetPtr = packet.readPacket(false);
	int counter=0;
	while(packetPtr != 0)
	{
		vec.push_back(packetPtr);
		packetPtr = packet.readPacket(false);
		counter++;
	}
}

void CTAPacketBufferV::load(int first, int last)
{
	int counter = 0;
	ByteStreamPtr packetPtr;

	// skip elements preceeding first
	while(counter < first) {
		packetPtr = packet.readPacket(false);
		if(packetPtr == 0) break;
		counter++;
	}
	

	// envec elements from first to last
	do {
		packetPtr = packet.readPacket(false);
		if(packetPtr == 0) break;
		vec.push_back(packetPtr);
		counter++;
	}
	while(counter <= last);
}

ByteStreamPtr CTAPacketBufferV::getNext()
{
	if(currentIndex >= vec.size())
		currentIndex = 0;
	return vec[currentIndex++];
}



ByteStreamPtr CTAPacketBufferV::getByteStream(int index, dword sizeB) {

	ByteStreamPtr stream = vec[index];
	dword sizep = sizeB;
	if(!sizep) sizep = packet.getInputPacketDimension(stream);
	bool bigendian = packet.isBigendian();
	return ByteStreamPtr(new ByteStream(stream, sizep, bigendian));

}

ByteStreamPtr CTAPacketBufferV::getNextByteStream(dword sizeB) {

	if(currentIndexBS >= size())
		currentIndexBS = 0;
	return getByteStream(currentIndexBS++, sizeB);

}

bool CTAPacketBufferV::isBigendian() {
	return packet.isBigendian();
}


}

