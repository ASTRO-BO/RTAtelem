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
	class CTAPedestalHigh {


		public:
			CTAPedestalHigh(string packetConfig, string tmInputFileName = "", string tmOutputFileName = "");
			~CTAPedestalHigh();
			
			//set section -----------------------------

			void setSSC(word counter);
			void setMetadata(byte arrayID); 
			void setNumberOfTelescopes(word number);
			void setIndexOfCurrentTelescopes(word telescopeIndex);
			void setTelescopeId(word telescopeID);
			void setNumberOfPixels(word number);
			void setPixelId(word pixelIndex, word pixelID);
			void setPedestalHighValue(word pixelIndex, word PED_HIGH);
			void writePacket();
			void printPacket_output();
			
			//get section ----------------------------
			
			// Return a ByteStream* or 0 if there is no packets
			byte* readPacket();
			void printPacket_input();
			word getSSC();
			void getMetadata(byte &arrayID); 
			word getNumberOfTelescopes();
			word getIndexOfCurrentTelescopes();
			word getTelescopeId();
			word getNumberOfPixels();
			word getPixelId(word pixelIndex);
			word getPedestalHighValue(word pixelIndex);
			
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
