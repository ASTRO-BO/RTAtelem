/***************************************************************************
 CTAPedestalHigh.h  -  description
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

#ifndef _CTAPEDESTAL_H
#define _CTAPEDESTAL_H

#include "CTACamera.h"

namespace RTATelem {

/// Creating and writing a packet for each CTA telescope,
/// containg the pedestal high value for each telescope pixel
/// \brief CTA pedestal high packet class
class CTACameraCharacterization : public CTACamera {

public:
	/// It takes the configuration file .stream and the input/output file name
	/// \param packetConfig The packet configuration file (.stream)
	/// \param tmInputFileName The input file name of the packet
	/// \param tmOutputFileName The output file name of the packet
	CTACameraCharacterization(string packetConfig, string tmInputFileName = "",
			string tmOutputFileName = "");

	~CTACameraCharacterization();

	/// It sets the telescope ID (identification number)
	/// \param telescopeID The telescope unique ID
	void setTelescopeId(word telescopeID);

	/// It gets the telescope ID (identification number)
	word getTelescopeId();

	/// It sets the number of pixels
	/// \param number The number of pixels
	void setNumberOfPixels(word number);

	/// It sets the pixel ID (identification number)
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param pixelID The pixel unique ID
	void setPixelId(word pixelIndex, word pixelID);

	/// It sets the pedestal high value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param PED_HIGH The pedestal high values of the pixel pixelIndex
	void setPedestalValue(word pixelIndex, word value);

	/// It gets the number of pixels
	word getNumberOfPixels();

	/// It gets the pixel ID (identification number)
	word getPixelId(word pixelIndex);

	/// It gets the pixel pedestal high value
	word getPedestalValue(word pixelIndex);

	word getChannel();

	void setChannel(word channel);

	word getPedestalRun();

	void setPedestalRun(word pede);


};
}

#endif
