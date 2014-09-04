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

#include "CTADecoder.h"
#include <packet/Packet.h>

using PacketLib::ByteStreamPtr;
using PacketLib::byte;

namespace RTATelem
{

CTADecoder::CTADecoder(const string& packetConfig)
	: _config(packetConfig), _cameraTD0(0), _cameraTD1(0),
	  _cameraP0(0), _cameraP1(0), _cameraC0(0), _cameraC1(0),
	  _unknownPacket(0)
{
	try
	{
		_ps.setFileNameConfig(packetConfig.c_str());
		_ps.createStreamStructure();
	}
	catch (PacketException* e)
	{
		std::cout << "Error on CTADecoder constructor: ";
		std::cout << e->geterror() << std::endl;
	}

}

CTAPacket& CTADecoder::getPacket(ByteStreamPtr stream)
{
	CTAPacket& packetRef = _unknownPacket;

	byte id = _ps.detPacketType(stream);
	PacketLib::Packet* p = _ps.getPacketType(id);
	switch(id)
	{
		case 1: case 2: case 3:
			packetRef = _cameraTD1;
			break;
		default:
			std::cerr << "Warning on CTADecoder::getPacket: ";
			std::cerr << " unhandled id " << id << std::endl;
	}

	packetRef.setPacket(p);

	return packetRef;
}

enum CTAPacketType CTADecoder::getPacketType(ByteStreamPtr stream)
{
	byte id = _ps.detPacketType(stream);
	switch(id)
	{
		case 1:
			return CTA_CAMERA_TRIGGERDATA_1; // modificato da VF
			return CTA_CAMERA_PEDESTAL_1;
			return CTA_CAMERA_CONVERSION_1;
		case 2: case 3:
			return CTA_CAMERA_TRIGGERDATA_1;

		default:
			std::cerr << "Warning on CTADecoder::getPacketType: ";
			std::cerr << " unhandled id " << id << std::endl;
	}

	return CTA_CAMERA_UNDEFINED;
}

}
