/***************************************************************************
    begin                : Mar 06 2014
    copyright            : (C) 2014 Andrea Bulgarelli, Andrea Zoli
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

#ifndef _CTACAMERATRIGGERDATA0_H
#define _CTACAMERATRIGGERDATA0_H

#include "CTACameraTriggerData.h"

namespace RTATelem {

/// Creating and writing a packet for each CTA triggered telescope,
/// containg the FADC value at each sample of the telescope pixel
/// \brief CTA triggered telescope packet class
class CTACameraTriggerData0 : public CTACameraTriggerData {

public:
    /// It wraps a PacketLib Packet.
	CTACameraTriggerData0(Packet* packet);

    /// Get the data of a pixel as stream of byte. Example about how to use this stream:
    /// ByteStreamPtr fadc = trtel->getPixelData(0);
	/// cout << fadc->printStreamInHexadecimal() << endl;
    /// cout << fadc->size() << endl;
	/// fadc->swapWordForIntel();
	/// word *c = (word*) fadc->stream;
	/// cout << "pixel id " << c[0] << endl;
	/// cout << "number of slices " << c[1] << endl;
	/// cout << "value of first slice " << c[2] << endl;
    /// \param The index of the pixel
    /// \return ByteStream of the pixel.
    ByteStreamPtr getPixelData(word pixelIndex);

    /// It gets the number of samples
    word getNumberOfSamples(word pixelIndex);

    /// It gets the sample FADC value
    word getSampleValue(word pixelIndex, word sampleIndex);
};

}

#endif
