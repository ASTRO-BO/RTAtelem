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

#include "CTAPacket.h"

using namespace std;

namespace RTATelem
{

CTAPacket::CTAPacket(Packet* packet)
	: header(0), _type(CTA_CAMERA_UNDEFINED)
{
	setPacket(packet);
}

void CTAPacket::setPacket(PacketLib::Packet* packet)
{
	if(packet)
	{
		_packet = packet;
		header.setPacket(packet);
	}
}


void CTAPacket::decode(bool checkPacketLength)
{
	if(_packet)
		_packet->decode(_packet->getBSPacket(), checkPacketLength);
}

void CTAPacket::printPacket()
{
	cout << "HEADER ----------" << endl;
	PacketLib::PacketHeader* h = _packet->getPacketHeader();
	char** r = h->printValue();
	_printListOfString(r);
	cout << h->getByteStream()->printStreamInHexadecimal() << endl;
	cout << "max dimension: " << h->size() << endl;
	cout << "packet length " << h->getPacketLength() << endl;

	cout << "DATA FIELD HEADER ----------" << endl;
	r = _packet->getPacketDataFieldHeader()->printValue();
	_printListOfString(r);
	cout << "max dimension: " << _packet->getPacketDataFieldHeader()->size() << endl;

	cout << "SOURCE DATA FIELD ----------" << endl;
	SourceDataField* sdf = (SourceDataField*) _packet->getPacketSourceDataField();
	cout << "max dimension: " << sdf->size() << endl;
	sdf->printValueStdout();

	cout << "TOTAL DIM OF THE PACKET : " << _packet->size() << endl;
	cout << "MAXDIM OF THE PACKET : " << _packet->sizeMax() << endl;
}

}
