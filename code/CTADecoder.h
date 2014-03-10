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

#ifndef _CTADECODER_H
#define _CTADECODER_H

#include <string>
#include <packet/ByteStream.h>
#include <packet/PacketStream.h>
#include "CTAPacket.h"

namespace RTATelem
{

class CTADecoder
{
public:

	CTADecoder(const string& packetConfig);

	CTAPacket* decode(PacketLib::ByteStreamPtr stream);

	PacketLib::dword getInputPacketDimension(PacketLib::ByteStreamPtr stream)
	{
		return _ps.getPacketDimension(stream);
	}

private:
	std::string _config;

	PacketLib::PacketStream _ps;
};

}

#endif
