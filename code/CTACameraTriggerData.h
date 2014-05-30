/***************************************************************************
    begin                : Mar 6 2014
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

#ifndef _CTACAMERATRIGGERDATA_H
#define _CTACAMERATRIGGERDATA_H

#include "CTACamera.h"

namespace RTATelem {

#define RBLOCK_PIXEL 0
#define RBLOCK_SAMPLE 0

/// Creating and writing a packet for each CTA triggered telescope,
/// containg the FADC value at each sample of the telescope pixel
/// \brief CTA triggered telescope packet class
class CTACameraTriggerData : public CTACamera {

public:
    /// It wraps PacketLib Packet.
	CTACameraTriggerData(Packet* packet);

	/// It sets the telescope ID (identification number)
	/// \param telescopeID The telescope unique ID
	void setTelescopeId(word telescopeID);

	/// It gets the telescope ID (identification number)
	word getTelescopeId();

	void setEventNumber(dword event);

	dword getEventNumber();

    /// It sets the number of triggered telescopes
    /// \param number Number of triggered telescopes
    void setNumberOfTriggeredTelescopes(byte number);

    /// It gets the number of triggered telescopes
    byte getNumberOfTriggeredTelescopes();

    /// It sets the index of the telescope converted to packet
    /// \param telescopeIndex The index of the written telescope (0..NumberOfTelescopes-1)
    void setIndexOfCurrentTriggeredTelescope(byte telescopeIndex);
	
    /// It gets the index of the telescope converted to packet
    byte getIndexOfCurrentTriggeredTelescope();

	/// It sets the pixel ID (identification number)
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param pixelID The pixel unique ID
    void setPixelId(word pixelIndex, word pixelID);
	
    /// It gets the pixel ID (identification number)
    word getPixelId(word pixelIndex);

	/// It sets the number of pixel blocks 
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param pixelID The pixel unique ID
    void setPixelBlocks(word numberOfCameraPixels);
	

	/// It sets the sample value for a fixed number of samples
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param sampleIndex The index of the sample (0..NumberOfSamples-1)
    /// \param FADC The FADC values of the sample sampleIndex of the pixel pixelIndex
    void setSampleValueFixed(word pixelIndex, word sampleIndex, word FADC);
	
    /// It gets the number of pixel blocks 
    //word setPixelBlocks(word pixelIndex);


    /// It sets the number of samples
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param number The number of samples of the pixel pixelIndex
    void setNumberOfSamples(word pixelIndex, word number);

    /// It sets the sample FADC value
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param sampleIndex The index of the sample (0..NumberOfSamples-1)
    /// \param FADC The FADC values of the sample sampleIndex of the pixel pixelIndex
    void setSampleValue(word pixelIndex, word sampleIndex, word FADC);
};

}

#endif
