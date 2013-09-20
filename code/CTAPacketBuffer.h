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
#ifndef _CTAPACKETBUFFER_H
#define _CTAPACKETBUFFER_H

#include <string>
#include <queue>
#include "PacketLibDefinition.h"

namespace RTATelem {

/// A FIFO queue of raw packets.
class CTAPacketBuffer {

public:
	CTAPacketBuffer(std::string packetConfig, std::string tmInputFileName);

	~CTAPacketBuffer();

	/// Load all the tmInputFile packets into the queue.
	void load();

	/// Load a subset of packets into the queue.
	/// \param first The first packet.
	/// \param last The last packet.
	void load(int first, int last);

	/// Push a raw packet to the queue.
	/// \param rawPacket The raw packet pointer.
	void push(byte* rawPacket)
	{
		queue.push(rawPacket);
	}

	/// Pop a raw packet from the queue.
	/// \return The raw packet pointer.
	byte* pop()
	{
		if(queue.size() == 0)
			return 0;

		byte* elem = queue.front();
		queue.pop();
		return elem;
	}

	/// Return the size of the queue.
	/// \return The size of the queue.
	int size()
	{
		return queue.size();
	}

private:
	CTAPacket packet;
	std::queue<byte*> queue;

};

}

#endif
