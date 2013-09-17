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
#include "OutputPacketStream.h"
#include "InputPacketStream.h"
#include "ByteStream.h"
#include "Output.h"
#include "Input.h"
#include "Packet.h"
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

	void printListOfString(char** r);

	void printListOfString(string* r);

public:

	CTAPacket(string packetConfig, string tmInputFileName, string tmOutputFileName);

	CTAPacket(string packetConfig);

	~CTAPacket();

	///It returns the total dimension of the packet contained in the stream (without prefix). The stream* contains also the prefix (if present)
	///\param The stream with the prefix (if present)
	dword getInputPacketDimension(byte* stream);

	/// Common header for all the packets (packet header + data field header)
	CTAPacketHeader* header;

	/// Writing the packet
	void writePacket();

	/// Printing the created packet
	void printPacket_output();

	/// Return a ByteStream* or 0 if there is no packets
	byte* readPacket();

	/// Printing the packet in input
	void printPacket_input();

	/// Get a pointer to telemetry packet
	ByteStream* getInputPacketData();
};

}

#endif
