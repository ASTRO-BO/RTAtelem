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

#ifndef _CTASTREAM_H
#define _CTASTREAM_H

#include <string>
#include <iostream>

#include <packet/Output.h>
#include <packet/Input.h>
#include <packet/Packet.h>
#include <packet/OutputPacketStream.h>
#include <packet/InputPacketStream.h>
#include <packet/ByteStream.h>

using PacketLib::dword;

namespace RTATelem {

class CTAStream
{
public:

	CTAStream(const std::string& packetConfig, const std::string& tmInputFileName, const std::string& tmOutputFileName);

	~CTAStream();

	/// Read a packet from input
	/// \return a ByteStreamPtr or 0 if there is no more packets
	PacketLib::ByteStreamPtr readPacket();

	/// Writing the packet
	void writePacket(PacketLib::ByteStreamPtr p);

	///It returns the total dimension of the packet contained in the stream (without prefix). The stream* contains also the prefix (if present)
	///\param The stream with the prefix (if present)
	dword getInputPacketDimension(PacketLib::ByteStreamPtr stream);

	/// Encapsulate the packet inside the CTAStream.
	void readPacketEnc();

	/// Get the dimension of the last packet read with readPacketEnc.
	dword getInputPacketDimensionEnc();

	const string& getPacketStreamConfig() const {
		return _config;
	}

private:

	PacketLib::Input* _in;
	PacketLib::Output* _out;
	PacketLib::InputPacketStream* _ips;
	PacketLib::OutputPacketStream* _ops;
	PacketLib::ByteStreamPtr _stream;
	std::string _config;
};

}

#endif
