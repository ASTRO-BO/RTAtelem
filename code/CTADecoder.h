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
#include "CTACameraTriggerData0.h"
#include "CTACameraTriggerData1.h"
#include "CTACameraPedestal.h"
#include "CTACameraPedestal1.h"
#include "CTACameraConv0.h"
#include "CTACameraConv1.h"

namespace RTATelem
{

class CTADecoder
{
public:

	CTADecoder(const string& packetConfig);

	CTAPacket& getPacket(PacketLib::ByteStreamPtr stream);

	enum CTAPacketType getPacketType(PacketLib::ByteStreamPtr stream);

	PacketLib::dword getInputPacketDimension(PacketLib::ByteStreamPtr stream)
	{
		return _ps.getPacketDimension(stream);
	}

private:
	std::string _config;

	PacketLib::PacketStream _ps;

	CTACameraTriggerData0 _cameraTD0;
	CTACameraTriggerData1 _cameraTD1;
	CTACameraPedestal _cameraP0;
	CTACameraPedestal1 _cameraP1;
	CTACameraConv0 _cameraC0;
	CTACameraConv1 _cameraC1;
	CTAPacket _unknownPacket;
};

}

#endif
