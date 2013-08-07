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

#ifndef _CTATRIGGEREDTELESCOPE_H
#define _CTATRIGGEREDTELESCOPE_H

#endif 

#include <iostream>
#include <stdlib.h>
#include "OutputPacketStream.h"
#include "InputPacketStream.h"
#include "ByteStream.h"
#include "Output.h"
#include "Input.h"
#include "Packet.h"

using namespace std;
using namespace PacketLib;

namespace RTATelem {
    /// Creating and writing a packet for each CTA triggered telescope, 
    /// containg the FADC value at each sample of the telescope pixel
    /// \brief CTA triggered telescope packet class
	class CTATriggeredTelescope {


		public:
            /// It takes the configuration file .stream and the input/output file name
		    /// \param packetConfig The packet configuration file (.stream)
		    /// \param tmInputFileName The input file name of the packet
		    /// \param tmOutputFileName The output file name of the packet
		    CTATriggeredTelescope(string packetConfig, string tmInputFileName = "", string tmOutputFileName = "");
			~CTATriggeredTelescope();
			

			/// It sets the Source Sequence Counter
			/// \param counter The value of the Source Sequence
			void setSSC(word counter);
			/// It sets the Metadata values
			/// \param arrayID The array unique ID
			/// \param runNumberID The run unique ID
			/// \param eventNumberID The event unique ID
			void setMetadata(byte arrayID, word runNumberID, dword eventNumberID); 
			/// It sets the telescope trigger time
			/// \param trigTime The telescope trigger time
			void setTelescopeTime(signed long trigTime); 
			/// It sets the number of triggered telescopes
			/// \param number Number of triggered telescopes
			void setNumberOfTriggeredTelescopes(word number);
			/// It sets the index of the telescope converted to packet
			/// \param telescopeIndex The index of the written telescope (0..NumberOfTelescopes-1)
			void setIndexOfCurrentTriggeredTelescopes(word telescopeIndex);
			/// It sets the telescope ID (identification number)
			/// \param telescopeID The telescope unique ID
			void setTelescopeId(word telescopeID);
			/// It sets the number of pixels
			/// \param number The number of pixels
			void setNumberOfPixels(word number);
			/// It sets the pixel ID (identification number)
			/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
			/// \param pixelID The pixel unique ID
			void setPixelId(word pixelIndex, word pixelID);
			/// It sets the number of samples 
			/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
			/// \param number The number of samples of the pixel pixelIndex
			void setNumberOfSamples(word pixelIndex, word number);
			/// It sets the sample FADC value 
			/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
			/// \param sampleIndex The index of the sample (0..NumberOfSamples-1)
			/// \param FADC The FADC values of the sample sampleIndex of the pixel pixelIndex
			void setSampleValue(word pixelIndex, word sampleIndex, word FADC);
			/// Writing the packet
			void writePacket();
			/// Printing the created packet
			void printPacket_output();
			
			
			/// Return a ByteStream* or 0 if there is no packets
			byte* readPacket();
			/// Printing the packet in input
			void printPacket_input();
			/// It gets the Source Sequence Counter
			word getSSC();
			/// It gets the Metadata values
			void getMetadata(byte &arrayID, word &runNumberID, dword &eventNumberID); 
			/// It gets the telescope trigger time
			signed long getTelescopeTime();
			/// It gets the number of triggered telescopes
			word getNumberOfTriggeredTelescopes();
			/// It gets the index of the telescope converted to packet
			word getIndexOfCurrentTriggeredTelescopes();
			/// It gets the telescope ID (identification number)
			word getTelescopeId();
			/// It gets the number of pixels
			word getNumberOfPixels();
			/// It gets the pixel ID (identification number)
			word getPixelId(word pixelIndex);
			/// It gets the number of samples 
			word getNumberOfSamples(word pixelIndex);
			/// It gets the sample FADC value 
			word getSampleValue(word pixelIndex, word sampleIndex);
			
		protected:
		
			/// Utility method 
			void printListOfString(char** r);
			/// Utility method 
			void printListOfString(string* r);
			
			
		protected:
			Output* out;
			Input* in;
       		OutputPacketStream* ops;
       		InputPacketStream* ips;
       		Packet* inputPacket;
       		Packet* outputPacket;		
       
       		
	};
}
