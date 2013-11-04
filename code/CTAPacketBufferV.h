/***************************************************************************
 CTAPacketBufferV.h  -  An array buffer class for Packets
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
#ifndef _CTAPACKETBUFFERV_H
#define _CTAPACKETBUFFERV_H

#include <string>
#include <vector>
#include "PacketLibDefinition.h"

namespace RTATelem {

/// An array of raw packets.
class CTAPacketBufferV {

public:
	CTAPacketBufferV(std::string packetConfig, std::string tmInputFileName);

	~CTAPacketBufferV();

	/// Load all the tmInputFile packets into the vector.
	void load();

	/// Load a subset of packets into the vector.
	/// \param first The first packet.
	/// \param last The last packet.
	void load(int first, int last);

	/// Get a raw packet.
	/// \index the index of the packet.
	byte* get(int index)
	{
		return vec[index];
	}

	ByteStream* getByteStream(int index, dword sizeB = 0);

	ByteStream* getNextByteStream(dword sizeB = 0);

	/// Get a raw packet (cyclic vector)
	byte* getNext();

	/// Return the size of the vector.
	/// \return The size of the vector.
	int size()
	{
		return vec.size();
	}

	CTAPacket packet;

	bool isBigendian();

private:

	std::vector<byte*> vec;
	long currentIndex;
	long currentIndexBS;

};

}

#endif