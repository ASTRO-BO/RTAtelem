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
	class CTATriggeredTelescope {


		public:
			CTATriggeredTelescope(string packetConfig, string tmInputFileName = "", string tmOutputFileName = "");
			~CTATriggeredTelescope();
			
			//set section -----------------------------

			void setMetadata(word arrayID, word runNumberID, word eventNumberID); 
			void setNumberOfTriggeredTelescopes(word number);
			void setIndexOfCurrentTriggeredTelescopes(word telescopeIndex);
			void setTelescopeId(word telescopeID);
			void setNumberOfPixels(word number);
			void setPixelId(word pixelIndex, word pixelID);
			void setNumberOfSamples(word pixelIndex, word number);
			void setSampleValue(word pixelIndex, word sampleIndex, word FADC);
			void writePacket();
			void printPacket_output();
			
			//get section ----------------------------
			
			// Return a ByteStream* or 0 if there is no packets
			byte* readPacket();
			void printPacket_input();
			void getMetadata(word &arrayID, word &runNumberID, word &eventNumberID); 
			word getNumberOfTriggeredTelescopes();
			word getIndexOfCurrentTriggeredTelescopes();
			word getTelescopeId();
			word getNumberOfPixels();
			word getPixelId(word pixelIndex);
			word getNumberOfSamples(word pixelIndex);
			word getSampleValue(word pixelIndex, word sampleIndex);
			
		protected:
		
			//utility
			void printListOfString(char** r);
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
