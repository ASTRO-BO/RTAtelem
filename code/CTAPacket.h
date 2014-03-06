/***************************************************************************
 CTAPacket.h
 -------------------
 copyright            : (C) 2013 Andrea Bulgarelli
 email                : bulgarelli@iasfbo.inaf.it
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
#include <iostream>
#include <stdlib.h>
#include <packet/OutputPacketStream.h>
#include <packet/InputPacketStream.h>
#include <packet/ByteStream.h>
#include <packet/Output.h>
#include <packet/Input.h>
#include <packet/Packet.h>
#include "CTAPacketHeader.h"

using namespace std;
using namespace PacketLib;

namespace RTATelem {

/// Base class for RTA source packets
/// \brief Base class for RTA source packets
class CTAPacket {

protected:
	Output* out;
	Input* in;
	OutputPacketStream* ops;
	InputPacketStream* ips;
	Packet* inputPacket;
	Packet* outputPacket;
	ByteStreamPtr pyStream;

	string packetStreamConfig;

	void printListOfString(char** r);

	void printListOfString(string* r);

public:

	CTAPacket(const string& packetConfig, const string& tmInputFileName, const string& tmOutputFileName);

	CTAPacket(const string& packetConfig);

	~CTAPacket();

	///It returns the total dimension of the packet contained in the stream (without prefix). The stream* contains also the prefix (if present)
	///\param The stream with the prefix (if present)
	dword getInputPacketDimension(ByteStreamPtr stream);
	dword getInputPacketDimension();
	
	int getInputPacketType(ByteStreamPtr stream);

	/// Common header for all the packets (packet header + data field header)
	CTAPacketHeader* header;

	/// Writing the packet
	void writePacket();

	/// Printing the created packet
	void printPacket_output();

	/// Read a packet from input
	/// \param decodeType 0 - do not decode, 1 - decode only sections, 2 - decode all blocks
	/// \return a ByteStreamPtr or 0 if there is no packets
	ByteStreamPtr readPacket(int decodeType);

	/// Read a packet from input
	/// \param decodeType 0 - do not decode, 1 - decode only sections, 2 - decode all blocks
	void readPacketPy(int decodeType);

	bool setStream(ByteStreamPtr stream, bool onlySections = false);

	/// Printing the packet in input
	void printPacket_input();

	/// Get a pointer to telemetry packet
	ByteStreamPtr getInputPacketData();

	const string& getPacketStreamConfig() const {
		return packetStreamConfig;
	}


	bool isBigendian() {
		return inputPacket->isBigendian();
	}
	
protected:
	
	ByteStreamPtr stream;
};

}

#endif
