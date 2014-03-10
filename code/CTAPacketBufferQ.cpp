/***************************************************************************
 CTAPacketBufferQ.h  -  A FIFO buffer class for Packets
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
#include "CTAPacketBufferQ.h"

namespace RTATelem
{

CTAPacketBufferQ::CTAPacketBufferQ(string packetConfig, string tmInputFile) : packet(packetConfig, tmInputFile, "")
{
}

CTAPacketBufferQ::~CTAPacketBufferQ()
{
}

void CTAPacketBufferQ::load()
{
	ByteStreamPtr packetPtr = packet.readPacket();
	int counter=0;
	while(packetPtr != 0)
	{
		push(packetPtr);
		packetPtr = packet.readPacket();
		counter++;
	}
}

void CTAPacketBufferQ::load(int first, int last)
{
	int counter = 0;
	ByteStreamPtr packetPtr;

	// skip elements preceeding first
	while(counter < first) {
		packetPtr = packet.readPacket();
		if(packetPtr == 0) break;
		counter++;
	}

	// enqueue elements from first to last
	do {
		packetPtr = packet.readPacket();
		if(packetPtr == 0) break;
		queue.push(packetPtr);
		counter++;
	}
	while(counter <= last);
}

}
