/***************************************************************************
 CTAPacketBuffer.h  -  A FIFO buffer class for Packets
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
#include "CTAPacketBuffer.h"

namespace RTATelem
{

CTAPacketBuffer::CTAPacketBuffer(string packetConfig, string tmInputFile) : packet(packetConfig, tmInputFile, "")
{
}

CTAPacketBuffer::~CTAPacketBuffer()
{
}

void CTAPacketBuffer::load()
{
	byte* packetPtr = packet.readPacket();
	int counter=0;
	while(packetPtr != 0)
	{
		push(packetPtr);
		packetPtr = packet.readPacket();
		counter++;
	}
}

void CTAPacketBuffer::load(int first, int last)
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
