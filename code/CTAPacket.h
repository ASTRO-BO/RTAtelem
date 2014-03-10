/***************************************************************************
 copyright            : (C) 2013-2014 Andrea Bulgarelli, Andrea Zoli
 email                : bulgarelli@iasfbo.inaf.it, zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef _CTAPACKET_H
#define _CTAPACKET_H

#include <packet/Packet.h>
#include <packet/ByteStream.h>
#include "CTAPacketHeader.h"

namespace RTATelem {

enum CTAPacketType
{
	CTA_CAMERA_UNDEFINED = 0,
	CTA_CAMERA_TRIGGERDATA_0,
	CTA_CAMERA_TRIGGERDATA_1,
	CTA_CAMERA_PEDESTAL_0,
	CTA_CAMERA_PEDESTAL_1,
	CTA_CAMERA_CONV_0,
	CTA_CAMERA_CONV_1,
};

/// Base class for RTA source packets
/// \brief Base class for RTA source packets
class CTAPacket {

public:

	/// Common header for all the packets (packet header + data field header)
	CTAPacketHeader* header;

	CTAPacket(PacketLib::Packet* packet);

	/// Printing the packet
	void printPacket();

	/// Get a pointer to telemetry packet
	PacketLib::ByteStreamPtr getInputPacketData()
	{
		return _packet->getBSPacket();
	}
	
	bool isBigendian() {
		return _packet->isBigendian();
	}
	
protected:

	enum CTAPacketType _type;

	PacketLib::Packet* _packet;

	void _printListOfString(char** r)
	{
		int i = 0;
		while (r[i] != 0)
			std::cout << r[i++] << std::endl;
	}

	//TODO maybe it is not needed
/*	void _printListOfString(std::string* r)
	{
		std::cout << *r << std::endl;
	}*/
};

}

#endif
