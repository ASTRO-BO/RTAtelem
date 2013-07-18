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
	class CTATriggeredEvent {


		public:
			CTATriggeredEvent(string packetConfig, string tmInputFileName = "", string tmOutputFileName = "");
			~CTATriggeredEvent();
			
			//set section -----------------------------
			
			
			void setMetadata(word arrayID, word runNumber, word eventNumber); 
			void setNumberOfTelescopes(word number);
			void setNumberOfPixels(word telescopeIndex, word number);
			void setNumerOfSamples(word telescopeIndex, word pixelIndex, word number);
			void setTelescopeId(word telescopeIndex, word telescopeID);
			void setPixelId(word telescopeIndex, word pixelIndex, word pixelID);
			void setSampleValue(word telescopeIndex, word pixelIndex, word sampleIndex, word FADC);
			void writePacket();
			
			//get section ----------------------------
			
			// Return a ByteStream* or 0 if there is no packets
			char* readPacket();
			
		protected:
			
			
		protected:
			Output* out;
			Input* in;
       		OutputPacketStream* ops;
       		InputPacketStream* ips;
       		Packet* inputPacket;
       		Packet* outputPacket;		
       
       		
	};
}
