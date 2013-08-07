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

#ifndef _CTAPEDESTALHIGH_H
#define _CTAPEDESTALHIGH_H

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
    /// Creating and writing a packet for each CTA telescope, 
    /// containg the pedestal high value for each telescope pixel
    /// \brief CTA pedestal high packet class
	class CTAPedestalHigh {


		public:
            /// It takes the configuration file .stream and the input/output file name
	        /// \param packetConfig The packet configuration file (.stream)
	        /// \param tmInputFileName The input file name of the packet
	        /// \param tmOutputFileName The output file name of the packet
			CTAPedestalHigh(string packetConfig, string tmInputFileName = "", string tmOutputFileName = "");
			~CTAPedestalHigh();
			
			//set section -----------------------------

			/// It sets the Source Sequence Counter
			/// \param counter The value of the Source Sequence
			void setSSC(word counter);
			/// It sets the Metadata values
			/// \param arrayID The array unique ID
			void setMetadata(byte arrayID); 
			/// It sets the number of telescopes
			/// \param number Total number of telescopes
			void setNumberOfTelescopes(word number);
			/// It sets the index of the telescope converted to packet
			/// \param telescopeIndex The index of the written telescope (0..NumberOfTelescopes-1)
			void setIndexOfCurrentTelescopes(word telescopeIndex);
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
			/// It sets the pedestal high value 
			/// \param pixelIndex The index of the pixel (0..NumberOfPixels-1)
			/// \param PED_HIGH The pedestal high values of the pixel pixelIndex
			void setPedestalHighValue(word pixelIndex, word PED_HIGH);
			/// Writing the packet
			void writePacket();
			/// Printing the created packet
			void printPacket_output();
			
			//get section ----------------------------
			
			/// Return a ByteStream* or 0 if there is no packets
			byte* readPacket();
			/// Printing the packet in input
			void printPacket_input();
			/// It gets the Source Sequence Counter
			word getSSC();
			/// It gets the Metadata values
			void getMetadata(byte &arrayID); 
			/// It gets the number of telescopes
			word getNumberOfTelescopes();
			/// It gets the index of the telescope converted to packet
			word getIndexOfCurrentTelescopes();
			/// It gets the telescope ID (identification number)
			word getTelescopeId();
			/// It gets the number of pixels
			word getNumberOfPixels();
			/// It gets the pixel ID (identification number)
			word getPixelId(word pixelIndex);
			/// It gets the pixel pedestal high value 
			word getPedestalHighValue(word pixelIndex);
			
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

#endif 