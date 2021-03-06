/***************************************************************************
 CTACameraConv0.h  -  description
 -------------------
 copyright            : (C) 2014 Valentina Fioretti
 email                : fioretti@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef _CTACAMERACONV0_H
#define _CTACAMERACONV0_H

#include "CTACameraConv.h"

namespace RTATelem {

/// Creating and writing a packet for each CTA telescope,
/// containg the pedestal value for each telescope pixel
/// Use setChannel() to set the pedestal channel (e.g. high or low).
/// \brief CTA pedestal packet class
class CTACameraConv0 : public RTATelem::CTACameraConv {

public:
    /// It wraps a PacketLib Packet.
	CTACameraConv0(Packet* packet);
    
	/// It sets the telescope ID (identification number)
	/// \param telescopeID The telescope unique ID
	void setTelescopeId(word telescopeID);

	/// It gets the telescope ID (identification number)
	word getTelescopeId();

	/// Set the conversion run (a run identifier within the current array run)
	word getConversionRun();

	/// Get the conversion run.
	void setConversionRun(word conv);
	
	/// It sets the pixel ID (identification number)
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param pixelID The pixel unique ID
	void setPixelId(word pixelIndex, word pixelID);

	/// It gets the pixel ID (identification number)
	word getPixelId(word pixelIndex);
	
	/// It sets the conversion high value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param convHigh The conversion high values of the pixel pixelIndex
	void setConversionHighValue(word pixelIndex, float convHigh);

	/// It gets the pixel conversion high value
	float getConversionHighValue(word pixelIndex);

	/// It sets the conversion low value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param convLow The conversion high values of the pixel pixelIndex
	void setConversionLowValue(word pixelIndex, float convLow);

	/// It gets the pixel conversion low value
	float getConversionLowValue(word pixelIndex);
	
    /// Get the data of a pixel as stream of byte. Example about how to use this stream:
    /// ByteStreamPtr convVal = convtel->getPixelData(0);
	/// cout << convVal->printStreamInHexadecimal() << endl;
    /// cout << convVal ->size() << endl;
	/// conv->swapWordForIntel();
	/// word *c = (word*) convVal->stream;
	/// cout << "pixel id " << c[0] << endl;
	/// cout << "number of summing windows " << c[1] << endl;
	/// cout << "value of first pedestal value " << c[2] << endl;
    /// \param The index of the pixel
    /// \return ByteStream of the pixel.
    ByteStreamPtr getPixelData(word pixelIndex);
    
};
}

#endif
