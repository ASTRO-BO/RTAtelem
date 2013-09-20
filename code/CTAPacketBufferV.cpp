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

namespace RTATelem
{

CTAPacketBufferV::CTAPacketBufferV(string packetConfig, string tmInputFile) : packet(packetConfig, tmInputFile, "")
{
	currentIndex = 0;
}

CTAPacketBufferV::~CTAPacketBufferV()
{
}

void CTAPacketBufferV::load()
{
	byte* packetPtr = packet.readPacket();
	int counter=0;
	while(packetPtr != 0)
	{
		vec.push_back(packetPtr);
		packetPtr = packet.readPacket();
		counter++;
	}
}

void CTAPacketBufferV::load(int first, int last)
{
	int counter = 0;
	byte* packetPtr;

	// skip elements preceeding first
	do {
		packetPtr = packet.readPacket();
		if(packetPtr == 0) break;
		counter++;
	}
	while(counter < first);

	// envec elements from first to last
	do {
		packetPtr = packet.readPacket();
		if(packetPtr == 0) break;
		vec.push_back(packetPtr);
		counter++;
	}
	while(counter <= last);
}

byte* CTAPacketBufferV::get()
{
	if(currentIndex >= size())
		currentIndex = 0;
	return vec[currentIndex++];
}

}
