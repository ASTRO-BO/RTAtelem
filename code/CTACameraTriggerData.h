/***************************************************************************
                          CTATriggeredTelescope.h  -  description
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

#ifndef _CTACAMERATRIGGERDATA_H
#define _CTACAMERATRIGGERDATA_H
#include "CTACamera.h"

namespace RTATelem {

/// Creating and writing a packet for each CTA triggered telescope,
/// containg the FADC value at each sample of the telescope pixel
/// \brief CTA triggered telescope packet class
class CTACameraTriggerData : public RTATelem::CTACamera {


public:
    /// It takes the configuration file .stream and the input/output file name
    /// \param packetConfig The packet configuration file (.stream)
    /// \param tmInputFileName The input file name of the packet
    /// \param tmOutputFileName The output file name of the packet
	CTACameraTriggerData(string packetConfig, string tmInputFileName = "", string tmOutputFileName = "");

    virtual ~CTACameraTriggerData();

	/// It sets the telescope ID (identification number)
	/// \param telescopeID The telescope unique ID
	virtual void setTelescopeId(word telescopeID);

	/// It gets the telescope ID (identification number)
	virtual word getTelescopeId();

	void setEventNumber(dword event);

	dword getEventNumber();

    /// It sets the number of triggered telescopes
    /// \param number Number of triggered telescopes
    void setNumberOfTriggeredTelescopes(byte number);

    /// It sets the index of the telescope converted to packet
    /// \param telescopeIndex The index of the written telescope (0..NumberOfTelescopes-1)
    void setIndexOfCurrentTriggeredTelescopes(byte telescopeIndex);

    /// It sets the pixel ID (identification number)
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param pixelID The pixel unique ID
    virtual void setPixelId(word pixelIndex, word pixelID);

    /// It gets the pixel ID (identification number)
    virtual word getPixelId(word pixelIndex);

    ByteStream* getPixelData(word pixelIndex);

    /// It sets the number of samples
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param number The number of samples of the pixel pixelIndex
    void setNumberOfSamples(word pixelIndex, word number);

    /// It sets the sample FADC value
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param sampleIndex The index of the sample (0..NumberOfSamples-1)
    /// \param FADC The FADC values of the sample sampleIndex of the pixel pixelIndex
    void setSampleValue(word pixelIndex, word sampleIndex, word FADC);

    /// It gets the number of triggered telescopes
    byte getNumberOfTriggeredTelescopes();

    /// It gets the index of the telescope converted to packet
    byte getIndexOfCurrentTriggeredTelescopes();

    /// It gets the number of samples
    word getNumberOfSamples(word pixelIndex);

    /// It gets the sample FADC value
    word getSampleValue(word pixelIndex, word sampleIndex);


};
}

#endif
