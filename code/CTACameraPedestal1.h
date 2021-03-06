/***************************************************************************
 CTACameraPedestal1.h  -  description
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

#ifndef _CTACAMERAPEDESTAL1_H
#define _CTACAMERAPEDESTAL1_H
#include "CTACamera.h"
#include "CTACameraPedestal.h"

namespace RTATelem {


//#define RBLOCK_PIXELID 1

/// Creating and writing a packet for each CTA telescope,
/// containg the pedestal value for each telescope pixel
class CTACameraPedestal1 : public CTACameraPedestal {

public:
	/// Wraps PacketLib Packet.
	CTACameraPedestal1(Packet* packet);

	PacketLib::ByteStreamPtr getInputPacketData();
	
	/// It sets the telescope ID (identification number)
	/// \param telescopeID The telescope unique ID
	void setTelescopeId(word telescopeID);

	/// It gets the telescope ID (identification number)
	word getTelescopeId();

	/// Set the pedestal run (a run identifier within the current array run)
	word getPedestalRun();

	/// Get the pedestal run.
	void setPedestalRun(word pedestalRun);
	
	/// It gets the number of pixels
	word getNumberOfCalibrationPixels();

	/// It sets the number of pixels
	/// \param number The number of pixels
	void setNumberOfCalibrationPixels(word number);

	/// It sets the pedestal high value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param pedHigh The pedestal high values of the pixel pixelIndex
	void setPedestalHighValue(word pixelIndex, float pedHigh);

	/// It gets the pixel pedestal high value
	float getPedestalHighValue(word pixelIndex);

	/// It sets the pedestal low value
	/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
	/// \param pedLow The pedestal high values of the pixel pixelIndex
	void setPedestalLowValue(word pixelIndex, float pedLow);

	/// It gets the pixel pedestal low value
	float getPedestalLowValue(word pixelIndex);

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
    
	/// It sets the number of summing windows
	void setNumberSummingWindows(word pixelIndex, word nsumWindows);

	/// It gets the number of summing windows
	word getNumberSummingWindows(word pixelIndex);

    /// It sets the pedvar high value
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param sumWindIndex The index of the summing window (0..NumberOfSummingWindows-1)
    /// \param pedvarHigh The pedvar High values of the summing window sumWindIndex of the pixel pixelIndex
    void setPedVarHigh(word pixelIndex, word sumWindIndex, float pedvarHigh);

    /// It gets the pedvar High value
    float getPedVarHigh(word pixelIndex, word sumWindIndex);

    /// It sets the pedvar low value
    /// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
    /// \param sumWindIndex The index of the summing window (0..NumberOfSummingWindows-1)
    /// \param pedvarLow The pedvar Low values of the summing window sumWindIndex of the pixel pixelIndex
    void setPedVarLow(word pixelIndex, word sumWindIndex, float pedvarLow);

    /// It gets the pedvar High value
    float getPedVarLow(word pixelIndex, word sumWindIndex);
    
    /// It sets the summing window
    /// \param sumWindIndex The index of the summing window (0..NumberOfSummingWindows-1)
    /// \param sumWind The summing window values of the summing window sumWindIndex 
    void setSumWindows(word sumWindIndex, word sumWind);

    /// It gets the summing window
    word getSumWindows(word sumWindIndex);

    /// It sets the time zero for each pixel
    /// \param sumWindIndex The index of the summing window (0..NumberOfSummingWindows-1)
    /// \param sumWind The summing window values of the summing window sumWindIndex 
    void setTimeZero(word pixelIndex, float tzero);

    /// It gets the summing window
    float getTimeZero(word pixelIndex);
    
};
}

#endif
