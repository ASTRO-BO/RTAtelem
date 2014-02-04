/***************************************************************************
 CTACameraCharacterization.h  -  description
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

#ifndef _CTACAMERAPEDESTAL_H
#define _CTACAMERAPEDESTAL_H
#include "CTACamera.h"

namespace RTATelem {

/// Creating and writing a packet for each CTA telescope,
/// containg the pedestal value for each telescope pixel
/// Use setChannel() to set the pedestal channel (e.g. high or low).
/// \brief CTA pedestal packet class
class CTACameraPedestal : public RTATelem::CTACamera {

public:
	/// It takes the configuration file .stream and the input/output file name
	/// \param packetConfig The packet configuration file (.stream)
	/// \param tmInputFileName The input file name of the packet
	/// \param tmOutputFileName The output file name of the packet
	CTACameraPedestal(string packetConfig, string tmInputFileName, string tmOutputFileName);

	CTACameraPedestal(string packetConfig);
	
	~CTACameraPedestal();
    
	/// It sets the telescope ID (identification number)
	/// \param telescopeID The telescope unique ID
	void setTelescopeId(word telescopeID);

	/// It gets the telescope ID (identification number)
	word getTelescopeId();

	/// It sets the pixel ID (identification number)
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param pixelID The pixel unique ID
	void setPixelId(word pixelIndex, word pixelID);

	/// It gets the pixel ID (identification number)
	word getPixelId(word pixelIndex);
	
	/// It sets the pedestal high value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param PED_HIGH The pedestal high values of the pixel pixelIndex
	void setPedestalHighValue(word pixelIndex, float pedHigh);

	/// It gets the pixel pedestal high value
	float getPedestalHighValue(word pixelIndex);

	/// It sets the pedestal high value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param PED_LOW The pedestal high values of the pixel pixelIndex
	void setPedestalLowValue(word pixelIndex, float pedLow);

	/// It gets the pixel pedestal high value
	float getPedestalLowValue(word pixelIndex);

	/// Set the pedestal run (a run identifier within the current array run)
	word getPedestalRun();

	/// Get the pedestal run.
	void setPedestalRun(word pede);


};
}

#endif
