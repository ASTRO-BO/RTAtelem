/***************************************************************************
 CTAPacketHeader.h
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

#ifndef _CTAPACKETHEADER_H
#define _CTAPACKETHEADER_H

#include <iostream>
#include <stdlib.h>
#include "Packet.h"

using namespace PacketLib;

namespace RTATelem {

///The CTA header of the source packet (NB: packet header + data field header)
class CTAPacketHeader {

public:

	CTAPacketHeader(Packet* inputPacket, Packet* outputPacket);

	/// It sets the Source Sequence Counter
	/// \param counter The value of the Source Sequence
	void setSSC(word counter);

	/// It gets the Source Sequence Counter
	word getSSC();

	/// It sets the APID
	/// \param apid The APID
	void setAPID(word apid);

	/// It gets the APID
	word getAPID();

	/// It sets the Metadata values
	/// \param arrayID The array unique ID
	/// \param runNumberID The run unique ID
	void setMetadata(word arrayID, word runNumberID);

	/// It gets the Metadata values
	void getMetadata(word& arrayID, word& runNumberID);

	/// It sets the time of data acquisition
	/// \param  The time of data acquisition
	void setTime(signed long time);

	/// It gets the time of data acquisition
	signed long getTime();


private:

	Packet* inputPacket;

	Packet* outputPacket;

};
}

#endif
