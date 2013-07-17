#include <iostream.h>
#include <stdlib.h>
#include "OutputPacketStream.h"
#include "InputPacketStream.h"
#include "ByteStream.h"
#include "Output.h"
#include "Input.h"

using namespace std;
using namespace PacketLib;

namespace RTATelem {
	class CTATriggeredEvent {


		public:
			CTATriggeredEvent(string packetConfig, string tmInputFileName, string tmOutputFileName);
			
			//read section -----------------------------
			
			// Return a ByteStream* or 0 if there is no packets
			ByteStream* readPacket();
			int getNumberOfCameras();
			
			//write section ----------------------------
			
			void writePacket();
			
			
		protected:
			Output* out;
			Input* in;
       		OutputPacketStream* ops;
       		InputPacketStream* ips;
       		Packet* inputPacket;
       		Packet* outputPacket;		
       
       		
	};
}
