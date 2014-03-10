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
#include "CTACameraTriggerData0.h"
#include "CTACameraTriggerData1.h"
#include "CTACameraPedestal.h"
#include "CTACameraPedestal1.h"
#include "CTACameraConv0.h"
#include "CTACameraConv1.h"
#include <packet/Packet.h>

using PacketLib::ByteStreamPtr;
using PacketLib::byte;

namespace RTATelem
{

CTADecoder::CTADecoder(const string& packetConfig)
	: _config(packetConfig)
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

CTAPacket* CTADecoder::decode(ByteStreamPtr stream)
{
	CTAPacket* packet = 0;

	PacketLib::Packet* p = _ps.getPacket(stream);
	byte id = p->getPacketID();
	switch(id)
	{
		case CTA_CAMERA_TRIGGERDATA_0:
			packet = new CTACameraTriggerData0(p);
			break;
		case CTA_CAMERA_TRIGGERDATA_1:
			packet = new CTACameraTriggerData1(p);
			break;
		case CTA_CAMERA_PEDESTAL_0:
			packet = new CTACameraPedestal(p);
			break;
		case CTA_CAMERA_PEDESTAL_1:
			packet = new CTACameraPedestal1(p);
			break;
		case CTA_CAMERA_CONV_0:
			packet = new CTACameraConv0(p);
			break;
		case CTA_CAMERA_CONV_1:
			packet = new CTACameraConv1(p);
			break;
		default:
			packet = 0;
	}

	return packet;
}

}
