/***************************************************************************
    begin                : TODO
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

#ifndef _CTACAMERATRIGGERDATA1_H
#define _CTACAMERATRIGGERDATA1_H

#include "CTACameraTriggerData.h"

namespace RTATelem {

#define RBLOCK_PIXELID 1

/// Creating and writing a packet for each CTA triggered telescope,
/// containg the FADC value at each sample of the telescope pixel
/// \brief CTA triggered telescope packet class
class CTACameraTriggerData1 : public CTACameraTriggerData {

public:
    /// It takes the configuration file .stream and the input/output file name
    /// \param packetConfig The packet configuration file (.stream)
    /// \param tmInputFileName The input file name of the packet
    /// \param tmOutputFileName The output file name of the packet
	CTACameraTriggerData1(string packetConfig, string tmInputFileName, string tmOutputFileName);

	CTACameraTriggerData1(string packetConfig);

    ~CTACameraTriggerData1();

	void writePacket();

	/// It sets the number of pixels IDs
	/// \param number The number of pixels IDs
	void setNumberOfPixelsID(word number);

	/// It gets the number of pixels IDs
	word getNumberOfPixelsID();

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
	
	ByteStreamPtr getCameraDataSlow();

    /// It gets the number of samples
    word getNumberOfSamples(word pixelIndex);

    /// It gets the sample FADC value
    word getSampleValue(word pixelIndex, word sampleIndex);
};
}

#endif
