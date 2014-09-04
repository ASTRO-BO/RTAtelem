/***************************************************************************
 CTACameraConv1.h  -  description
 -------------------
 copyright            : (C) 2013 Andrea Bulgarelli
                            2014 Valentina Fioretti
 email                : bulgarelli@iasfbo.inaf.it
                        fioretti@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef _CTACAMERACONV1_H
#define _CTACAMERACONV1_H
#include "CTACamera.h"
#include "CTACameraConv.h"

namespace RTATelem {



/// Creating and writing a packet for each CTA telescope,
/// containing the conversion factor value for each telescope pixel
/// \brief CTA conversion packet class
class CTACameraConv1 : public CTACameraConv {

public:
	/// Wraps PacketLib Packet.
	CTACameraConv1(Packet* packet);

	PacketLib::ByteStreamPtr getInputPacketData();
	
	/// It sets the telescope ID (identification number)
	/// \param telescopeID The telescope unique ID
	void setTelescopeId(word telescopeID);

	/// It gets the telescope ID (identification number)
	word getTelescopeId();

	/// Set the conversion run (a run identifier within the current array run)
	word getConversionRun();

	/// Get the conversion run.
	void setConversionRun(word conversionRun);
	
	/// It gets the number of pixels
	word getNumberOfCalibrationPixels();

	/// It sets the number of pixels
	/// \param number The number of pixels
	void setNumberOfCalibrationPixels(word number);

	/// It sets the conversion high value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param convHigh The conversion high values of the pixel pixelIndex
	void setConversionHighValue(word pixelIndex, float convHigh);

	/// It gets the pixel pedestal high value
	float getConversionHighValue(word pixelIndex);

	/// It sets the conversion low value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param convLow The conversion high values of the pixel pixelIndex
	void setConversionLowValue(word pixelIndex, float convLow);

	/// It gets the pixel conversion low value
	float getConversionLowValue(word pixelIndex);

    /// Get the data of a pixel as stream of byte. Example about how to use this stream:
    /// ByteStreamPtr pedVal = pedtel->getPixelData(0);
	/// cout << pedVal->printStreamInHexadecimal() << endl;
    /// cout << pedVal ->size() << endl;
	/// fadc->swapWordForIntel();
	/// word *c = (word*) pedVal->stream;
	/// cout << "pixel id " << c[0] << endl;
	/// cout << "number of summing windows " << c[1] << endl;
	/// cout << "value of first pedestal value " << c[2] << endl;
    /// \param The index of the pixel
    /// \return ByteStream of the pixel.
    ByteStreamPtr getPixelData(word pixelIndex);

};
}

#endif
