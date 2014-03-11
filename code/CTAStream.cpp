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

#include "CTAStream.h"
#include "CTACameraTriggerData0.h"
#include "CTACameraTriggerData1.h"
#include "CTACameraPedestal.h"
#include "CTACameraPedestal1.h"
#include "CTACameraConv0.h"
#include "CTACameraConv1.h"
#include <packet/InputFile.h>
#include <packet/OutputFile.h>

using namespace std;
using namespace PacketLib;

namespace RTATelem
{

CTAStream::CTAStream(const string& packetConfig, const string& tmInputFileName, const string& tmOutputFileName)
	: _in(0), _out(0), _ips(0), _ops(0), _config(packetConfig)
{
	try
	{
		char** param = (char**) new char*[2];

		if(tmOutputFileName != "")
		{
			// create output packet stream
			_ops = new OutputPacketStream();
			_ops->setFileNameConfig(_config.c_str());
			_ops->createStreamStructure();
			//cout << (const char*) outputPacket->getName() << endl;
			// parameter for the output: file
			_out = (Output*) new OutputFile(_ops->isBigEndian());
			// file name
			param[0] = (char*) tmOutputFileName.c_str();
			param[1] = 0;

			// open output
			_out->open(param);

			// connect the output
			_ops->setOutput(_out);
		}
		if(tmInputFileName != "")
		{
			/// create input packet stream
			_ips = new InputPacketStream();
			_ips->setFileNameConfig(_config.c_str());
			_ips->createStreamStructure();

			_in = (Input*) new InputFile(_ips->isBigEndian());
			/// file name
			param[0] = (char*) tmInputFileName.c_str();
			param[1] = 0;

			/// open input
			_in->open(param);

			/// set a particular input
			_ips->setInput(_in);

		}
	}
	catch (PacketException* e)
	{
		cout << "Error on CTAStream constructor: ";
		cout << e->geterror() << endl;
	}
}

CTAStream::~CTAStream() {
	delete _ips;
	delete _ops;
	if (_in)
		_in->close();
	if (_out)
		_out->close();
}

ByteStreamPtr CTAStream::readPacket()
{
	Packet* inputPacket = _ips->readPacket();
	if (inputPacket == 0)
		return 0;

	return inputPacket->getInputStream();
}

CTAPacket* CTAStream::getNewPacket(enum CTAPacketType type)
{
	// get id from enum
	PacketLib::byte id = 0;
	switch(type)
	{
		case CTA_CAMERA_TRIGGERDATA_1:
			id = 1;
			break;

		case CTA_CAMERA_UNDEFINED:
		default:
			id = 0;
	}

	// get Packet from id
	PacketLib::PacketStream* ps = 0;
	if(_ips)
		ps = _ips;
	if(_ops)
		ps = _ops;
	if(ps == 0)
		return 0;
	Packet* p = ps->getPacketType(id);

	// allocate the right CTAPacket
	CTAPacket* packet;
	switch(type)
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
		case CTA_CAMERA_UNDEFINED:
		default:
			packet = 0;
	}

	return packet;
}

void CTAStream::writePacket(ByteStreamPtr p)
{
	_ops->writePacket(p);
}

void CTAStream::readPacketEnc()
{
	_stream = readPacket();
}


dword CTAStream::getInputPacketDimension(PacketLib::ByteStreamPtr stream)
{
	return _ips->getPacketDimension(stream);
}

dword CTAStream::getInputPacketDimensionEnc()
{
	return _ips->getPacketDimension(_stream);
}

}
